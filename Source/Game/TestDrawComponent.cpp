#include "Game/TestDrawComponent.h"
#include <DxLib.h>


void TestDrawComponent::Update(float deltaTime)
{
	_x += _speed * deltaTime;
	if (_x > 800.0f) {
		_x = 0.0f;
	}
}