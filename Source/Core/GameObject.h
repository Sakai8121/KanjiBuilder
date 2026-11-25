#pragma once

#include "Core/Component.h"
#include "Core/Handle.h"
#include "Core/TransformComponent.h"
#include <vector>
#include <memory>
#include <utility>


// コンポーネントを入れるだけの入れ物。継承しない
class GameObject final
{
public:
	GameObject(Handle handle, Scene* scene) : _handle(handle), _scene(scene)
	{
		_transform = AddComponent<TransformComponent>();
	}
	~GameObject() = default;

	void Start();
	void Update(float deltaTime);
	Handle GetHandle() const { return _handle; }

	void SetActive(bool isActive) { _isActive = isActive; }
	bool IsActive() const { return _isActive; }

	// Update中に呼ばれるDestroyでフラグを立てるだけ
	void Destroy() { _isDestroyed = true; }
	bool IsDestroyed() const { return _isDestroyed; }
	// 遅延破棄の処理
	void OnDestroy();

	// TransformComponentは専用アクセサを用意しておく
	TransformComponent* GetTransform() const { return _transform; }

	// このゲームオブジェクトが所属するシーンの公開
	Scene* GetScene() const { return _scene; }

	// コンポーネントを追加し、参照用の生ポインタを返す
	template <typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		auto comp = std::make_unique<T>(
			std::forward<Args>(args)...
		);

		T* rawPtr = comp.get();

		rawPtr->_gameObject = this;
		_components.push_back(std::move(comp));

		rawPtr->OnAttach(); // 所有者（gameObject）が確定した後に行う初期化
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
	TransformComponent* _transform = nullptr;
	Scene* _scene = nullptr;

	// ゲームオブジェクトがアクティブかどうか
	bool _isActive = true;	
	// 遅延破棄用
	bool _isDestroyed = false;

	// 無効な状態があることに注意。デフォルト初期化は無効な状態で初期化される
	Handle _handle;
};