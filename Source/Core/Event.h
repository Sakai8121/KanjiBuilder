#pragma once

struct IEvent
{
	virtual ~IEvent() = default;
};

struct EnemyDeadEvent : public IEvent
{
	int deadPositionX;
};