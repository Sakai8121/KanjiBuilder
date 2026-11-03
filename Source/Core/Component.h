#pragma once

class GameObject;

class Component
{
	friend class GameObject;

public:
	virtual ~Component() = default;
	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void Draw() {};

protected:
	GameObject* gameObject = nullptr;
};