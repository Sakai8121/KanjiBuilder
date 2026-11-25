#include "Core/Component.h"
#include "Core/GameObject.h"

void Component::SetActive(bool isActive)
{
	_isActive = isActive;
}

bool Component::IsActive() const
{
	return _isActive;
}

void Component::Destroy()
{
	OnDestroy();
}

Scene* Component::GetScene() const
{
	return _gameObject->GetScene();
}
