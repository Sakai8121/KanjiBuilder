#pragma once
#include <vector>
#include "Core/Handle.h"

class GameObject;

class SlotMap final
{
	struct Slot
	{
		GameObject* gameObject = nullptr;
		unsigned int generation = 1; // 初期は１
	};

public:
	// GameObjectをスロットに追加し、Handleを返す
	Handle Insert(GameObject* gameObject);
	// Handleを使ってGameObjectを取得する
	GameObject* Get(const Handle& handle) const;
	// Handleを使ってGameObjectを削除する
	void Remove(const Handle& handle);

private:
	std::vector<Slot> slots;
	// 削除されて空いたスロットのインデックスを保持する配列
	std::vector<unsigned int> freeIndices;
};

