#pragma once
#include <cstdint>

namespace m
{
	void Setup();

	// Return pointer to virtual function
	constexpr void* Get(void* thisptr, const size_t index) noexcept
	{
		return (*static_cast<void***>(thisptr))[index];
	}

	// Wrapper to call virtual functions
	template <typename T, typename ... U>
	constexpr T Call(void* thisptr, const size_t index, U ... params) noexcept
	{
		using Fn = T(__thiscall*)(void*, decltype(params)...);
		return (*static_cast<Fn**>(thisptr))[index](thisptr, params...);
	}

	// Convert and address from relative to absolute
	template <typename T = uintptr_t>
	constexpr T RelativeToAbsolute(const uintptr_t address) noexcept
	{
		return static_cast<T>(address + 4 + *reinterpret_cast<uint32_t*>(address));
	}

	inline struct Sigs
	{
		uint8_t* glowObjectManager = nullptr;
		uint8_t* weaponSystem = nullptr;
		uint8_t* viewRenderBeams = nullptr;
		uint8_t* device = nullptr;
		uint8_t* hud = nullptr;
		uint8_t* staticPropMgr = nullptr;
		uint8_t* findElement = nullptr;
		uint8_t* keyValuesFromString = nullptr;
		uint8_t* setAbsOrigin = nullptr;
		uint8_t* setAbsAngles = nullptr;
		uint8_t* startDrawing = nullptr;
		uint8_t* finishDrawing = nullptr;
		uint8_t* insertIntoTree = nullptr;
		uint8_t* getPlayerMoney = nullptr;
		uint8_t* settingsChatText = nullptr;
		uint8_t* showAlert = nullptr;
		uint8_t* staticPropInit = nullptr;
		uint8_t* allocKeyValuesEngine = nullptr;
		uint8_t* allocKeyValuesClient = nullptr;
	}sigs;

	// Signature scanner :)
	uint8_t* Scan(const char* module, const char* pattern);
}
