#pragma once
#include "../sdk/definitions.h"
#include "../other/fnv.h"

#include <map>
#include <type_traits>

namespace n
{
	// Run once to dump all netvars
	void Setup() noexcept;

	// Loops through data tables and places offsets & props into the "prop" map
	void Dump(const char* baseClass, RecvTable* table, const std::uint32_t offset);

	// Get desired data
	std::uint32_t GetOffset(const std::uint32_t hash);
	RecvProp* GetProp(const std::uint32_t hash);

	struct NetvarData
	{
		RecvProp* prop = { };
		std::uint32_t  offset = { };
	};

	inline std::map<uint32_t, NetvarData> data = { };
}

#define NETVAR(name, var, ...) \
std::add_lvalue_reference_t<__VA_ARGS__> name() \
{ \
	static const auto offset = n::GetOffset(fnv::HashConst(var)); \
	return *reinterpret_cast<std::add_pointer_t<__VA_ARGS__>>(std::uintptr_t(this) + offset); \
}

#define NETPROP(name, var) \
static RecvProp* name() \
{ \
	static auto prop = n::GetProp(fnv::HashConst(var)); \
	return prop; \
}
