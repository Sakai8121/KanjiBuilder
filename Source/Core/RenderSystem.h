#pragma once
#include <vector>

class RendererComponent;

class RenderSystem final
{
public:
	RenderSystem() = default;
	~RenderSystem() = default;

	// Sceneごとに1つ所有させるため、コピー禁止
	RenderSystem(const RenderSystem&) = delete;
	RenderSystem& operator=(const RenderSystem&) = delete;

	void Register(RendererComponent* renderer);
	void Unregister(RendererComponent* renderer);

	// レイヤーや順序が変更された際にRendererComponentから呼ばれる
	void MarkDirty() { _isDirty = true; }

	// ソートした上で全有効レンダラーを描画
	void Render();
private:
	std::vector<RendererComponent*> _renderers;
	bool _isDirty = false;
};