#pragma once
#include "../definitions.h"

class InterfaceRegister
{
public:
	InstantiateInterfaceFn CreateInterface;
	const char* name;
	InterfaceRegister* next;
};
