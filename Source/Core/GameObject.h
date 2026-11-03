#pragma once

#include <Core/Component.h>

#include <vector>
#include <memory>
#include <utility>

class GameObject
{
public:
	virtual ~GameObject() = default;

	void Update(float deltaTime);
	void Draw();

	// コンポーネントを追加し、参照用の生ポインタを返す
	template <typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		auto comp = std::make_unique<T>(
			std::forward<Args>(args)...
		);

		T* rawPtr = comp.get();

		rawPtr->gameObject = this;

		components.push_back(std::move(comp));

		return rawPtr;
	}

	// 指定した型のコンポーネントを探して、生ポインタを返す
	template <typename T>
	T* GetComponent()
	{
		for (auto& comp : components)
		{
			if (T* casted = dynamic_cast<T*>(comp.get()))
			{
				return casted;
			}
		}

		return nullptr;
	}
private:
	std::vector<std::unique_ptr<Component>> components;
	bool isActive = true;
};