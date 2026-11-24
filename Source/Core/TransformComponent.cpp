#include "Core/TransformComponent.h"

TransformComponent::~TransformComponent()
{
	// 自身が破棄される際、親と子の参照を切り離してダングリングポインタを防ぐ
	if (_parent != nullptr)
	{
		_parent->RemoveChild(this);
		_parent = nullptr;
	}

	for (auto* child : _children)
	{
		if (child != nullptr)
		{
			child->SetParent(nullptr);
		}
	}
	_children.clear();
}

Vector2 TransformComponent::GetWorldPosition() const
{
	if (_parent == nullptr) return _localPosition;

	// 親のスケールの適用
	const Vector2 parentScale = _parent->GetWorldScale();
	const Vector2 scaledPos = {
		_localPosition.x * parentScale.x,
		_localPosition.y * parentScale.y
	};

	// 親のワールド回転角度分だけローカル座標を回転
	const float parentRad = _parent->GetWorldRotationRad();
	const float cosTheta = std::cos(parentRad);
	const float sinTheta = std::sin(parentRad);

	const Vector2 rotatedPos = {
		scaledPos.x * cosTheta - scaledPos.y * sinTheta,
		scaledPos.x * sinTheta + scaledPos.y * cosTheta
	};

	// 親のワールド座標に回転を考慮した座標を加算
	return _parent->GetWorldPosition() + rotatedPos;
}

float TransformComponent::GetWorldRotation() const
{
	if (_parent == nullptr) return _localRotation;
	return _parent->GetWorldRotation() + _localRotation;
}

Vector2 TransformComponent::GetWorldScale() const
{
	if (_parent == nullptr) return _localScale;
	return _parent->GetWorldScale() + _localScale;
}

void TransformComponent::LookAt(const Vector2& targetWorldPos)
{
	const Vector2 dir = targetWorldPos - GetWorldPosition();
	if (dir.LengthSq() <= 1e-6f) return;

	// atan2(y, x) で右向き(1, 0)を0度とした角度を算出
	const float worldAngleDeg =  Math::ToDegrees(std::atan2(dir.y, dir.x));

	if (_parent == nullptr)
	{
		_localRotation = worldAngleDeg;
	}
	else
	{
		_localRotation = worldAngleDeg - _parent->GetWorldRotation();
	}
}

void TransformComponent::SetParent(TransformComponent* newParent)
{
	if (_parent == newParent || _parent == this) return;

	if (_parent != nullptr)
	{
		_parent->RemoveChild(this);
	}

	_parent = newParent;

	if (_parent != nullptr)
	{
		_parent->_children.push_back(this);
	}
}

void TransformComponent::RemoveChild(TransformComponent* child)
{
	std::erase(_children, child);
}
