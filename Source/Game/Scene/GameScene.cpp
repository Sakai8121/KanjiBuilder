#include "Game/Scene/GameScene.h"
#include "Game/TestDrawComponent.h"
#include "Core/GameObject.h"

void GameScene::OnStart()
{
	// テスト用　あとで消す
	auto gameObject = std::make_unique<GameObject>(Handle());
	gameObject->AddComponent<TestDrawComponent>();
	_sceneGameObjects.push_back(std::move(gameObject));
}