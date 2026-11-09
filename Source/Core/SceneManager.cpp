#include "Core/SceneManager.h"
#include "Game/Scene/GameScene.h"
#include "Core/Logger.h"

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;
	return instance;
}

void SceneManager::Init()
{
	// 最初のシーンはとりあえずGameScene
	_stackScenes.push_back(std::make_unique<GameScene>());
	_stackScenes.back()->Start();
}

void SceneManager::RequestPush(std::unique_ptr<Scene> scene, const std::source_location& location)
{
	RegisterPendingAction(SceneAction::Push, std::move(scene), location);
}

void SceneManager::RequestPop(const std::source_location& location)
{
	// PopにはSceneが不要なので、nullptrを渡す
	RegisterPendingAction(SceneAction::Pop, nullptr, location);
}

void SceneManager::RequestChange(std::unique_ptr<Scene> scene, const std::source_location& location)
{
	RegisterPendingAction(SceneAction::Change, std::move(scene), location);
}

void SceneManager::RegisterPendingAction(
	SceneAction action,
	std::unique_ptr<Scene> scene,
	const std::source_location& location)
{
	if (_pendingAction != SceneAction::None)
	{
		Log::Error("同一フレーム内で複数のシーン操作が要求されました。", location);
		return;
	}

	_pendingAction = action;
	_pendingScene = std::move(scene); // Popの場合はnullptrが入るが問題ない
}

void SceneManager::ApplyPendingAction()
{
	if (_pendingAction == SceneAction::None) return;

	switch (_pendingAction)
	{
	case SceneAction::Push:
		_stackScenes.push_back(std::move(_pendingScene));
		_stackScenes.back()->Start();
		break;
	case SceneAction::Pop:
		if (!_stackScenes.empty()) _stackScenes.pop_back();
		break;
	case SceneAction::Change:
		_stackScenes.clear();
		_stackScenes.push_back(std::move(_pendingScene));
		_stackScenes.back()->Start();
		break;
	}

	_pendingAction = SceneAction::None;
}

void SceneManager::Update(float frameDt)
{
	if (!_stackScenes.empty()) 
	{
		_stackScenes.back()->Update(frameDt);
	}
}

void SceneManager::Draw()
{
	for (auto& scene : _stackScenes) 
	{
		scene->Draw();
	}
}

void SceneManager::ProcessGC()
{
	if (!_stackScenes.empty()) 
	{
		_stackScenes.back()->ProcessGC();
	}
}