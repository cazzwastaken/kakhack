#pragma once
#include "../definitions.h"

enum InitReturnVal : int
{
	INIT_FAILED = 0,
	INIT_OK,
	INIT_LAST_VAL,
};

enum AppSystemTier : int
{
	APP_SYSTEM_TIER0 = 0,
	APP_SYSTEM_TIER1,
	APP_SYSTEM_TIER2,
	APP_SYSTEM_TIER3,
	APP_SYSTEM_TIER_OTHER,
};

struct AppSystemInfo
{
	const char* moduleName;
	const char* interfaceName;
};

class AppSystem
{
public:
	virtual bool Connect(CreateInterfaceFn factory) = 0;
	virtual void Disconnect() = 0;
	virtual void* QueryInterface(const char* interfaceName) = 0;
	virtual InitReturnVal Init() = 0;
	virtual void Shutdown() = 0;
	virtual const AppSystemInfo* GetDependencies() = 0;
	virtual AppSystemTier GetTier() = 0;
	virtual void Reconnect(CreateInterfaceFn factory, const char* interfaceName) = 0;
	virtual bool IsSingleton() = 0;
};
