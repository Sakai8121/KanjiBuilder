#pragma once
#include <vector>
#include <functional>
#include <queue>
#include <memory>
#include "Core/Subscription.h"

struct IEvent;

using EventCallback = std::function<void(const IEvent*)>;

class EventBus final
{
public:
	// シングルトンにする
	// 深い階層までバケツリレーをしてコンストラクタが汚染されるデメリットを嫌って。
	static EventBus& GetInstance();

	Subscription Subscribe(EventCallback callback);
	void Unsubscribe(unsigned int id);

	// 即時発火しない。キューにためる。
	void Publish(std::unique_ptr<IEvent> event);
	// _eventQueueに溜まったすべてのイベントをまとめて発火する。
	void Flush();

private:
	// シングルトンにするため、外部からの生成・コピーを禁止
	EventBus() = default;
	~EventBus() = default;
	EventBus(const EventBus&) = delete;

	// IDと関数のペア
	std::vector<std::pair<unsigned int, EventCallback>> _subscribers;
	// 発行待ちのイベントを溜めるキュー
	std::queue<std::unique_ptr<IEvent>> _eventQueue;
	// 購読者に割り当てるIDのカウンター
	unsigned int _nextId = 0;
};

