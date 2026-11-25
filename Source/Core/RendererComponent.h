#pragma once
#include "Core/Component.h"
#include "Core/Interface/IRenderable.h"

// 描画コンポーネントの基底クラス
class RendererComponent : public Component, public IRenderable
{
public:
	RendererComponent(RenderLayer renderLayer = RenderLayer::Unit, int orderInLayer = 0)
		: _renderLayer(renderLayer), _orderInLayer(orderInLayer){ }
	// ~RendererComponent() は書かなくても親の virtual ~Component() と ~IRenderable() により安全に破棄される

	// IRenderable
	void Render() override = 0;
	bool IsRenderableActive() const override;
	RenderLayer GetRenderLayer() const override;
	int GetOrderInLayer() const override;

	// final をつけることで、派生クラスでオーバーライドさせず、OnRendererAttachやOnRendererDestroyをオーバーライドさせる
	// OnAttachとOnDestroyをオーバーライド出来るようにすると、このコンポーネントの呼び忘れが発生する可能性が高いから
	void OnAttach() final;
	void OnDestroy() final;

	void SetRenderLayer(RenderLayer);
	void SetOrderInLayer(int);

protected:
	// 派生クラスで初期化・後始末が必要なときは、こちらをオーバーライドする
	// OnAttachとOnDestroyを素直にオーバーライドさせたときの呼び忘れが物理的に不可能になる
	virtual void OnRendererAttach() {}
	virtual void OnRendererDestroy() {}

private:
	void MarkDirty();

	RenderLayer _renderLayer = RenderLayer::Unit; // 適当な初期化
	int _orderInLayer = 0;
	bool _isRegistered = false;
};