#pragma once

#include "Core/Component.h"
#include "Core/Handle.h"

#include <vector>
#include <memory>
#include <utility>

class GameObject
{
public:
	GameObject(Handle handle) : _handle(handle){}
	virtual ~GameObject() = default;

	void Update(float deltaTime);
	// 描画機能を持たないコンポーネントの空の実装を呼んでいたり、描画順を制御できない。
	// Todo: 描画機能を持つComponentが自分の画像と座標をグローバルなRenderManagerのようなものに送り、
	// まとめて描画フェーズで描画する形にする。
	// ※Update内で他のコンポーネントと合わせて描画すると、実行順序によって結果が変わるのでやらないように注意
	void Draw();
	Handle GetHandle() const;
	void SetActive(bool isActive);
	void Destory();
	bool IsDestroyed();
	virtual void OnDestroy() {};

	// コンポーネントを追加し、参照用の生ポインタを返す
	template <typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		auto comp = std::make_unique<T>(
			std::forward<Args>(args)...
		);

		T* rawPtr = comp.get();

		rawPtr->gameObject = this;

		_components.push_back(std::move(comp));

		return rawPtr;
	}

	// 指定した型のコンポーネントを探して、生ポインタを返す
	template <typename T>
	T* GetComponent()
	{
		for (auto& comp : _components)
		{
			if (T* casted = dynamic_cast<T*>(comp.get()))
			{
				return casted;
			}
		}

		return nullptr;
	}

private:
	std::vector<std::unique_ptr<Component>> _components;
	bool _isActive = true;
	// 遅延破棄用
	bool _isDestroyed = false;
	Handle _handle;
};