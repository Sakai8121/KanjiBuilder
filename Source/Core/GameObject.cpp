#include <Core/GameObject.h>

void GameObject::Update(float deltaTime)
{
	if (!isActive) return;
	for (auto& comp : components)
	{
		comp->Update(deltaTime);
	}
}

void GameObject::Draw()
{
	if (!isActive) return;
	for (auto& comp : components)
	{
		comp->Draw();
	}
}