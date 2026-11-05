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

void GameObject::Destory()
{
	OnDestroy();

	for (auto& comp : _components)
	{
		comp->Destroy();
	}

	_isDestroyed = true;
}

bool GameObject::IsDestroyed()
{
	return _isDestroyed;
}