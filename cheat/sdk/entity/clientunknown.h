#pragma once
#include "../definitions.h"

#include "handleentity.h"

class ClientUnknown : public HandleEntity
{
public:
	virtual Collideable* GetCollideable() = 0;
	virtual ClientNetworkable* GetClientNetworkable() = 0;
	virtual ClientRenderable* GetClientRenderable() = 0;
	virtual ClientEntity* GetClientEntity() = 0;
	virtual BaseEntity* GetBaseEntity() = 0;
	virtual ClientThinkable* GetClientThinkable() = 0;
	virtual ClientAlphaProperty* GetClientAlphaProperty() = 0;
};
