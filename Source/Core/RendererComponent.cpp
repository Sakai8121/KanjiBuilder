#include "Core/RendererComponent.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include <cassert>

bool RendererComponent::IsRenderableActive() const
{
	return GetGameObject() != nullptr && GetGameObject()->IsActive() && IsActive();
}

RenderLayer RendererComponent::GetRenderLayer() const
{
	return _renderLayer;
}

int RendererComponent::GetOrderInLayer() const
{
	return _orderInLayer;
}

void RendererComponent::OnAttach()
{
	assert(GetGameObject() != nullptr && GetGameObject()->GetScene() != nullptr);
	if (!_isRegistered)
	{
		GetGameObject()->GetScene()->GetRenderSystem().Register(this);
		_isRegistered = true;
	}

	// 派生クラスの追加処理（RenderSystemに登録された後の安全な状態）
	OnRendererAttach();
}

void RendererComponent::OnDestroy()
{
	// 先に派生クラスの処理（まだ RenderSystem に登録された安全な状態）
	OnRendererDestroy();

	if (_isRegistered && GetGameObject() != nullptr && GetGameObject()->GetScene() != nullptr)
	{
		GetGameObject()->GetScene()->GetRenderSystem().Unregister(this);
		_isRegistered = false;
	}
}

void RendererComponent::SetRenderLayer(RenderLayer renderLayer)
{
	if (_renderLayer != renderLayer)
	{
		_renderLayer = renderLayer;
		MarkDirty();
	}
}

void RendererComponent::SetOrderInLayer(int order)
{
	if (_orderInLayer != order)
	{
		_orderInLayer = order;
		MarkDirty();
	}
}

void RendererComponent::MarkDirty()
{
	if (GetGameObject() != nullptr && GetGameObject()->GetScene() != nullptr)
	{
		GetGameObject()->GetScene()->GetRenderSystem().MarkDirty();
	}
}
