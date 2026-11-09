#pragma once  
#include <vector>  
#include <memory>  
#include <Dxlib.h>
#include "Core/SlotMap.h"
#include "Core/GameObject.h"

class Scene  
{  
public:  
	void Start();  
	void Update(float frameDt);
	void Draw();
	void ProcessGC();

protected:
	virtual void OnStart() {};
	std::vector<std::unique_ptr<GameObject>> _sceneGameObjects;
	SlotMap _slotMap;
};
