#include "Core/GameObjectManager.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include <memory>

GameObject* GameObjectManager::Create(Scene* scene)
{
	unsigned int index;
	if (!_freeIndices.empty())
	{
		index = _freeIndices.back();
		_freeIndices.pop_back();
	}
	else
	{
		index = static_cast<unsigned int>(_slots.size());
		_slots.emplace_back();
	}

	Handle handle = Handle(index, _slots[index].generation);
	_slots[index].gameObject = std::make_unique<GameObject>(handle, scene);

	// 生成時に「Start待ちキュー」にハンドルを積んでおく
	_pendingStarts.push_back(handle);

	return _slots[index].gameObject.get();
}

GameObject* GameObjectManager::Get(const Handle& handle) const
{
	if (handle.Index < _slots.size() && _slots[handle.Index].generation == handle.Generation)
	{
		return _slots[handle.Index].gameObject.get();
	}

	return nullptr;
}

void GameObjectManager::Remove(const Handle& handle)
{
	if (handle.Index < _slots.size() && _slots[handle.Index].generation == handle.Generation)
	{
		_slots[handle.Index].gameObject = nullptr;
		_slots[handle.Index].generation++;
		_freeIndices.push_back(handle.Index);
	}
}

void GameObjectManager::UpdateAll(float deltaTime)
{
	// Updateを回す前に未スタートのオブジェクトを確実にStartさせる
	ProcessPendingStarts();

	// Indexでアクセスるのはvectorの再確保対策
	const size_t count = _slots.size();
	for (size_t i = 0; i < count; ++i)
	{
		if (_slots[i].gameObject)
		{
			// IsActive()判定はUpdate関数内で実行されている
			_slots[i].gameObject->Update(deltaTime);
		}
	}
}

void GameObjectManager::ProcessGC()
{
	if (_pendingDestroys.empty()) return;

	// OnDestroy の実行（キューの末尾に連鎖追加されてもインデックス走査ならそのまま処理できる）
	for (size_t i = 0; i < _pendingDestroys.size(); ++i)
	{
		if (GameObject* obj = Get(_pendingDestroys[i]))
		{
			obj->OnDestroy();
		}
	}

	// 全員の OnDestroy が終わってから一括でメモリ解放
	for (const Handle& handle : _pendingDestroys)
	{
		Remove(handle);
	}

	_pendingDestroys.clear();
}

void GameObjectManager::ProcessPendingStarts()
{
	// Start() 内でさらに SpawnGameObject() されたオブジェクトが、
	// Start() 未実行のまま直後の Update() に突入するのを防ぐため、空になるまで回す
	while (!_pendingStarts.empty())
	{
		// Start() 内の新規スポーンや非アクティブ持ち越しによる _pendingStarts への追加と走査の競合（イテレータ破壊）を防ぐ。
		// swap は要素のコピーではなく内部ポインタの交換（O(1)）でキューを切り離す。
		std::vector<Handle> currentBatch;
		currentBatch.swap(_pendingStarts);

		bool startedAny = false;
		for (const Handle& handle : currentBatch)
		{
			// Handle 経由で取得するため、Start前に破棄されていても nullptr になり安全
			if (GameObject* obj = Get(handle))
			{
				if (obj->IsActive())
				{
					obj->Start();
					startedAny = true;
				}
				else
				{
					// 非アクティブ状態で生成された場合は、アクティブになるまで持ち越す
					_pendingStarts.push_back(handle);
				}
			}
		}

		// 残っているのが「非アクティブで持ち越した要素」だけなら無限ループ防止のため抜ける
		if (!startedAny) break;
	}
}