#include "Game/TestDrawComponent.h"
#include <DxLib.h>


void TestDrawComponent::Update(float deltaTime)
{
	_x += _speed * deltaTime;
	if (_x > 800.0f) {
		_x = 0.0f;
	}
}

void TestDrawComponent::Draw()
{
	DrawBox(static_cast<int>(_x), static_cast<int>(_y), static_cast<int>(_x + 50.0f), static_cast<int>(_y + 50.0f), GetColor(255, 0, 0), TRUE);
}