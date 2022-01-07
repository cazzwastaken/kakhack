#pragma once
#include "../definitions.h"

#include <cstddef>
#include "../data/utlvector.h"

using CommandCallbackV1Fn = void(__cdecl*)();
using ChangeCallbackFn = void(__cdecl*)(void*, const char*, float);

class ConVar
{
public:
	const char* GetName()
	{
		return m::Call<const char*>(this, 5);
	}

	float GetFloat()
	{
		std::uint32_t xored = *reinterpret_cast<std::uint32_t*>(&parent->valueFloat) ^ reinterpret_cast<std::uint32_t>(this);
		return *reinterpret_cast<float*>(&xored);
	}

	int GetInt()
	{
		return static_cast<int>(parent->valueInt ^ reinterpret_cast<int>(this));
	}

	bool GetBool()
	{
		return !!GetInt();
	}

	const char* GetString() const
	{
		char const* szValue = parent->string;
		return szValue ? szValue : "";
	}

	void SetValue(const char* value)
	{
		m::Call<void>(this, 14, value);
	}

	void SetValue(float value)
	{
		m::Call<void>(this, 15, value);
	}

	void SetValue(int value)
	{
		return m::Call<void>(this, 16, value);
	}

public:
	std::byte pad0[0x4];
	ConVar* next;
	bool registered;
	const char* name;
	const char* helpString;
	int flags;
	CommandCallbackV1Fn callback;
	ConVar* parent;
	const char* defaultValue;
	char* string;
	int stringLength;
	float valueFloat;
	int valueInt;
	bool hasMin;
	float minValue;
	bool hasMax;
	float maxValue;
	UtlVector<ChangeCallbackFn>	changeCallbacks;
};
