#pragma once

class GameObject;
class Scene;

class Component
{
	friend class GameObject;

public:
	virtual ~Component() = default;
	virtual void Start() {};
	virtual void Update(float deltaTime) {};
	virtual void OnDestroy() {};
	// ゲームオブジェクトにアタッチされた直後に所有者（GameObjectやScene）
	// にアクセスできる状態で初期セットアップを行うため。
	// コンストラクタだと_gameObjectがセットされていなくてnullptrなのでだめ
	// Startだと遅すぎる
	virtual void OnAttach() {};

	void SetActive(bool isActive);
	bool IsActive() const;
	void Destroy();

	GameObject* GetGameObject() const { return _gameObject; };

protected:
	// Componentがシーン経由でシーンに紐づく公開APIにアクセスするために用意
	// オブジェクトの生成やレンダラーシステムなどのAPI
	// ※シーン固有のマネージャーはオブジェクトにアタッチする方式にするのでシーンの公開APIにしないことを注意
	Scene* GetScene() const;

private:
	GameObject* _gameObject = nullptr;
	bool _isActive = true;
};