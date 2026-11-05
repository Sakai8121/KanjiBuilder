#include <Core/GameObject.h>

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

void GameObject::Draw()
{
	if (!_isActive) return;
	for (auto& comp : _components)
	{
		if (comp->IsActive())
		{
			comp->Draw();
		}
	}
}

void GameObject::SetActive(bool isActive)
{
	_isActive = isActive;
}

Handle GameObject::GetHandle() const
{
	return _handle;
}