#include "Core/Scene.h"
#include "Core/GameObject.h"

void Scene::Start()
{
	OnStart();

	for (auto& gameObject : _sceneGameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update(LONGLONG frameDt)
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