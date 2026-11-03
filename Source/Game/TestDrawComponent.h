#pragma once
#include "Core/Component.h"

// GameObjectとComponent基底のテスト用のコンポーネント
class TestDrawComponent final : public Component
{
public:
	void Update(float deltaTime) override;
	void Draw() override;

private :
	float _x = 100.0f;
	float _y = 50.0f;
	float _speed = 100.0f;
};

