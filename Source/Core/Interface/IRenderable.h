#pragma once

// 描画レイヤーの定義（数値が小さいほど奥に描画される）
enum class RenderLayer : int
{
	Background = 0,
	Tower = 100, // 防衛対象のタワー
	Enemy = 200,
	Unit = 300, // 漢字パーツ
	Effect = 400,
	UI = 500
};

class IRenderable
{
public:
	// 実際の描画処理
	virtual void Render() = 0;

	// 描画するべき状態かどうか（「自身のIsActive」＆「GameObjectのIsActive」）
	virtual bool IsRenderableActive() const = 0;

	// 描画順の取得
	virtual RenderLayer GetRenderLayer() const = 0;
	virtual int GetOrderInLayer() const = 0;
};