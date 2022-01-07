#pragma once
#include "../entity/entity.h"

struct EntityCacheInfo
{
	ClientNetworkable* networkable;
	unsigned short baseEntitiesIndex;
	unsigned short dormant;
};

class ClientEntityListener
{
public:
	virtual void OnEntityCreated(BaseEntity* entity) = 0;
	virtual void OnEntityDeleted(BaseEntity* entity) = 0;
};

class ClientEntityList
{
public:
	virtual ClientNetworkable* GetClientNetworkable(int index) = 0;
	virtual ClientNetworkable* GetClientNetworkableFromHandle(BaseHandle handle) = 0;
	virtual ClientUnknown* GetClientUnknownFromHandle(BaseHandle handle) = 0;

	virtual ClientEntity* GetClientEntity(int index) = 0;
	virtual ClientEntity* GetClientEntityFromHandle(BaseHandle handle) = 0;

	virtual int NumberOfEntities(bool includeNonNetworkable) = 0;

	virtual int GetHighestEntityIndex(void) = 0;

	virtual void SetMaxEntities(int maxEntities) = 0;
	virtual int GetMaxEntities() = 0;
	virtual EntityCacheInfo* GetClientNetworkableArray() = 0;

	template <typename T = BaseEntity>
	constexpr T* Get(int index)
	{
		return static_cast<T*>(GetClientEntity(index));
	}

	template <typename T = BaseEntity>
	constexpr T* FromHandle(BaseHandle handle)
	{
		return static_cast<T*>(GetClientEntityFromHandle(handle));
	}

	void AddEntityListener(ClientEntityListener* listener)
	{
		listeners.AddToTail(listener);
	}

	void RemoveEntityListener(ClientEntityListener* listener)
	{
		listeners.FindAndRemove(listener);
	}

private:
	UtlVector<ClientEntityListener*> listeners;
};
