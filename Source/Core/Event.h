#pragma once
#include <memory>
#include <functional>
#include "Core/Scene.h"

struct IEvent
{
	virtual ~IEvent() = default;
};