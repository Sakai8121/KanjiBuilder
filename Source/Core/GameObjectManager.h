#pragma once
#include <vector>
#include <memory>
#include "Core/Handle.h"

class GameObject;
class Scene;

class GameObjectManager final
{
	struct Slot
	{
		std::unique_ptr<GameObject> gameObject = nullptr;
		unsigned int generation = 1; // 初期は１
	};

public:
	GameObjectManager() = default;
	~GameObjectManager() = default;

	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator=(const GameObjectManager&) = delete;

	// GameObjectを生成する。ハンドルも発行して設定している
	GameObject* Create(Scene* scene);

	// Handleを使ってGameObjectを取得する
	GameObject* Get(const Handle& handle) const;
	// Handleを使ってGameObjectを削除する
	void Remove(const Handle& handle);

	// シーン内の全有効オブジェクトの更新
	void UpdateAll(float deltaTime);

	// 破棄フラグが立ったオブジェクトの遅延破棄（GC）
	void ProcessGC();

	// Start処理を見実行のオブジェクトキュー（シーン初期化以外の動的スポーンに対応するため）
	void ProcessPendingStarts();

private:

	std::vector<Slot> _slots;
	// 削除されて空いたスロットのインデックスを保持する配列
	std::vector<unsigned int> _freeIndices;
	// Start待ちのハンドル一覧（動的スポーン時のStartの呼び出しに対応するため）
	std::vector<Handle> _pendingStarts;
	// Detroy待ちのハンドル一覧（OnDestroy内でオブジェクトが破棄されても問題ないようにするためと最適化）
	std::vector<Handle> _pendingDestroys;
};

