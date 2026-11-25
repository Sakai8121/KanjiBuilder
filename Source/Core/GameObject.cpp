#include <Core/GameObject.h>

void GameObject::Start()
{
	if (!_isActive) return;
	for (auto& comp : _components)
	{
		if (comp->IsActive())
		{
			comp->Start();
		}
	}
}

void GameObject::Update(float deltaTime)
{
	if (!_isActive) return;
	for (auto& comp : _components)
	{
		if (comp->IsActive())
		{
			comp->Update(deltaTime);
		}
	}
}

void GameObject::OnDestroy()
{
	for (auto& comp : _components)
	{
		comp->OnDestroy();
	}
}