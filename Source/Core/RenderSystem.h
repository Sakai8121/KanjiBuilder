#pragma once
#include <vector>

class IRenderable;

class RenderSystem final
{
public:
	RenderSystem() = default;
	~RenderSystem() = default;
	RenderSystem(RenderSystem&&) = default;
	RenderSystem& operator=(RenderSystem&&) = default;

	// Sceneごとに1つ所有させるため、コピー禁止
	RenderSystem(const RenderSystem&) = delete;
	RenderSystem& operator=(const RenderSystem&) = delete;

	void Register(IRenderable* renderer);
	void Unregister(IRenderable* renderer);

	// レイヤーや順序が変更された際にIRenderableから呼ばれる
	void MarkDirty() { _isDirty = true; }

	// ソートした上で全有効レンダラーを描画
	void Render();
private:
	std::vector<IRenderable*> _renderers;
	bool _isDirty = false;
};