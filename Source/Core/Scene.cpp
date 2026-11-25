#include "Core/Scene.h"
#include "Core/GameObject.h"

void Scene::Start()
{
	// 各シーンのスタート処理を呼ぶ
	OnStart();

	_objectManager.ProcessPendingStarts();
}

GameObject* Scene::SpawnGameObject()
{
	return _objectManager.Create(this);
}
