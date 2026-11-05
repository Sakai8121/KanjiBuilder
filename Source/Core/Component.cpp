#include "Core/Component.h"

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
	OnDestory();
}