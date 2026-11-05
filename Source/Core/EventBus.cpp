#include "Core/EventBus.h"
#include "Core/Event.h"
#include <algorithm>

EventBus& EventBus::GetInstance()
{
	static EventBus instance;
	return instance;
}

Subscription EventBus::Subscribe(EventCallback callBack)
{
	_nextId++;
	_subscribers.emplace_back(_nextId, std::move(callBack));
	return Subscription(_nextId);
}

void EventBus::Unsubscribe(unsigned int id)
{
	_subscribers.erase(
		std::remove_if(_subscribers.begin(), _subscribers.end(),
			[id](const auto& pair) { return pair.first == id; }),
		_subscribers.end());
}

void EventBus::Publish(std::unique_ptr<IEvent> event)
{
	_eventQueue.push(std::move(event));
}

void EventBus::Flush()
{
	while (!_eventQueue.empty())
	{
		auto event = std::move(_eventQueue.front());
		_eventQueue.pop();

		for (const auto& subscriber : _subscribers)
		{
			subscriber.second(event.get());
		}
	}
}