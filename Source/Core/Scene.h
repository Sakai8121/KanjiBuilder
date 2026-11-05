#pragma once  
#include <vector>  
#include <memory>  
#include <Dxlib.h>

class GameObject;  

class Scene  
{  
public:  
	void Start();  
	void Update(LONGLONG frameDt);
	void Draw();

protected:
	virtual void OnStart() {};
	std::vector<std::unique_ptr<GameObject>> _sceneGameObjects;
};
