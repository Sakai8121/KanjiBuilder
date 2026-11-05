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

	void SetActive(bool isActive);
	bool IsActive() const;

protected:
	GameObject* gameObject = nullptr;

private:
	bool _isActive = true;
};