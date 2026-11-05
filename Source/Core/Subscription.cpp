#include "Core/Subscription.h"
#include "Core/EventBus.h"

Subscription::~Subscription()
{
	if (_id != 0)
	{
		// 自分が破棄されるとき、自動的に EventBus から登録を消す
		EventBus::GetInstance().Unsubscribe(_id);
	}
}