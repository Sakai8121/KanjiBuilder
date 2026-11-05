#include "Core/SlotMap.h"

Handle SlotMap::Insert(GameObject* gameObject)
{
	unsigned int index;
	if (!freeIndices.empty()) 
	{
		index = freeIndices.back();
		freeIndices.pop_back();
	}
	else 
	{
		index = static_cast<unsigned int>(slots.size());
		slots.emplace_back();
	}
	slots[index].gameObject = gameObject;
	return Handle(index, slots[index].generation);
}

GameObject* SlotMap::Get(const Handle& handle) const
{
	if (handle.Index < slots.size() && slots[handle.Index].generation == handle.Generation)
	{
		return slots[handle.Index].gameObject;
	}

	return nullptr;
}

void SlotMap::Remove(const Handle& handle)
{
	if (handle.Index < slots.size() && slots[handle.Index].generation == handle.Generation)
	{
		slots[handle.Index].gameObject = nullptr;
		slots[handle.Index].generation++;
		freeIndices.push_back(handle.Index);
	}
}