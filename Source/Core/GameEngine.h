#pragma once
#include <vector>
#include <memory>
#include "Core/GameObject.h"

class GameEngine
{
public:
	GameEngine();
	void Loop();

private:
	std::vector<std::unique_ptr<GameObject>> _gameObjects;
};