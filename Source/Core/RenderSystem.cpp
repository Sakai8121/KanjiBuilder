#include "Core/RenderSystem.h"
#include "Core/RendererComponent.h"
#include <algorithm>

void RenderSystem::Register(RendererComponent* renderer)
{
	_renderers.push_back(renderer);
	MarkDirty();
}

void RenderSystem::Unregister(RendererComponent* renderer)
{
	std::erase(_renderers, renderer);
	MarkDirty();
}

void RenderSystem::Render()
{
	if (_isDirty)
	{

	}

	for (const auto* renderer : _renderers)
	{
		if (renderer->IsActive())
		{
			
		}
	}
}