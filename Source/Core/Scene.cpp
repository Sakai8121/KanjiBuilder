#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Core/Logger.h"

void Scene::Start()
{
	_slotMap = SlotMap();

	OnStart();

	for (auto& gameObject : _sceneGameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update(float frameDt)
{
	for (auto& gameObject : _sceneGameObjects)
	{
		gameObject->Update(frameDt);
	}
}

void Scene::Draw()
{
	for (auto& gameObject : _sceneGameObjects)
	{
		gameObject->Draw();
	}
}

void Scene::ProcessGC()
{
	// メモリから消える前にOnDestoryの処理を実行する
	for (auto& gameObject : _sceneGameObjects)
	{
		if (gameObject && gameObject->IsDestroyed())
		{
			gameObject->OnDestroy();
			_slotMap.Remove(gameObject->GetHandle());
		}
	}

	// メモリから削除
	std::erase_if(_sceneGameObjects, [](const auto& gameObject)
	{
		return gameObject == nullptr || gameObject->IsDestroyed();
	});
}