#pragma once
#include "Core/Component.h"
#include "Core/Vector2.h"
#include "Core/Math.h"
#include <vector>

class TransformComponent final : public Component
{
public:
	TransformComponent() = default;
	~TransformComponent() override;

	// ローカル
	void SetLocalPosition(const Vector2& pos) { _localPosition = pos; }
	void SetLocalPosition(float x, float y) { _localPosition = { x, y }; }
	Vector2 GetLocalPosition() const { return _localPosition; }

	void SetLocalRotation(float degrees) { _localRotation = degrees; }
	float GetLocalRotation() const { return _localRotation; }
	float GetLocalRotationRad() const { return Math::ToRadians(_localRotation); }

	void SetLocalScale(const Vector2& scale) { _localScale = scale; }
	void SetLocalScale(float uniformScale) { _localScale = { uniformScale, uniformScale }; }
	Vector2 GetLocalScale() const { return _localScale; }

	// ワールド
	Vector2 GetWorldPosition() const;
	float GetWorldRotation() const;
	float GetWorldRotationRad() const { return Math::ToRadians(GetWorldRotation()); }
	Vector2 GetWorldScale() const;

	// Transform操作
	void Translate(const Vector2& delta) { _localPosition += delta; }
	void Rotate(float deltaDegrees) { _localRotation += deltaDegrees; }
	void LookAt(const Vector2& targetWorldPos);

	// 親子関係
	void SetParent(TransformComponent* newParent);
	TransformComponent* GetParent() const { return _parent; }
	const std::vector<TransformComponent*> GetChildren() const { return _children; }

private:
	void RemoveChild(TransformComponent* child);

	Vector2 _localPosition = Vector2::Zero();
	float _localRotation = 0.0f;
	Vector2 _localScale = Vector2::One();

	TransformComponent* _parent = nullptr;
	std::vector<TransformComponent*> _children;
};

