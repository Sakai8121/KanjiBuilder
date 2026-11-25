#pragma once  
#include <vector>  
#include <memory>
#include "Core/GameObjectManager.h"
#include "Core/GameObject.h"
#include "Core/RenderSystem.h"
class Scene  
{  
public:
	Scene() = default;
	virtual ~Scene() = default;

	void Start();  
	void Update(float frameDt) { _objectManager.UpdateAll(frameDt); }
	void Draw() { _renderSystem.Render(); }
	void ProcessGC() { _objectManager.ProcessGC(); }

	// 派生シーンやコンポーネントからオブジェクトを生成する唯一の窓口
	GameObject* SpawnGameObject();
	GameObject* FindGameObject(const Handle& handle) const { return _objectManager.Get(handle); }
	RenderSystem& GetRenderSystem() { return _renderSystem; }

protected:
	virtual void OnStart() {};

private:
	RenderSystem _renderSystem;
	GameObjectManager _objectManager;
};
