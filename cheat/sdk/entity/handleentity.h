#pragma once
#include "../definitions.h"

class HandleEntity
{
public:
	virtual ~HandleEntity() { }
	virtual void SetRefEHandle(const BaseHandle& ref) = 0;
	virtual const BaseHandle& GetRefEHandle() const = 0;
};
