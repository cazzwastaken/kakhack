#include "../hooks.h"

#include <intrin.h>

void* __stdcall h::AllocKeyValuesMemory(int size)
{
	static const auto allocKeyValuesEngine = reinterpret_cast<std::uintptr_t>(m::sigs.allocKeyValuesEngine);
	static const auto allocKeyValuesClient = reinterpret_cast<std::uintptr_t>(m::sigs.allocKeyValuesClient);

	if (const auto retAddr = reinterpret_cast<std::uintptr_t>(_ReturnAddress());
		retAddr == allocKeyValuesEngine ||
		retAddr == allocKeyValuesClient)
		return nullptr;

	return AllocKeyValuesMemoryOriginal(i::keyValues, size);
}
