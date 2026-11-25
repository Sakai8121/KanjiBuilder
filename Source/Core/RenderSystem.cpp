#include "Core/RenderSystem.h"
#include "Core/Interface/IRenderable.h"
#include <algorithm>

void RenderSystem::Register(IRenderable* renderer)
{
	_renderers.push_back(renderer);
	MarkDirty();
}

void RenderSystem::Unregister(IRenderable* renderer)
{
	std::erase(_renderers, renderer);
}

void RenderSystem::Render()
{
	if (_isDirty)
	{
		// 同じレイヤーかつ同じオーダーのオブジェクトのちらつき防止のためStableSortを使う
		std::stable_sort(_renderers.begin(), _renderers.end(),
			[](const IRenderable* a, const IRenderable* b)
			{
				if (a->GetRenderLayer() != b->GetRenderLayer())
				{
					return a->GetRenderLayer() < b->GetRenderLayer();
				}
				else
				{
					return a->GetOrderInLayer() < b->GetOrderInLayer();
				}
			});
		
		_isDirty = false;
	}

	for (IRenderable* renderer : _renderers)
	{
		if (renderer->IsRenderableActive())
		{
			renderer->Render();
		}
	}
}