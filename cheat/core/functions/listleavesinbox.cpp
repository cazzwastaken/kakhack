#include "../hooks.h"

#include <intrin.h>

int __stdcall h::ListLeavesInBox(const Vector& mins, const Vector& maxs, unsigned short* list, int listMax)
{
	static const auto insertIntoTree = reinterpret_cast<std::uintptr_t>(m::sigs.insertIntoTree);

	if (reinterpret_cast<std::uintptr_t>(_ReturnAddress()) != insertIntoTree)
		return ListLeavesInBoxOriginal(i::engine->GetBSPTreeQuery(), mins, maxs, list, listMax);

	// No need to run this code if hidden chams aren't on
	if (!v::visuals.hidden.first)
		return ListLeavesInBoxOriginal(i::engine->GetBSPTreeQuery(), mins, maxs, list, listMax);

	const auto info = *reinterpret_cast<RenderableInfo**>(reinterpret_cast<std::uintptr_t>(_AddressOfReturnAddress()) + 0x14);

	if (!info || !info->renderable)
		return ListLeavesInBoxOriginal(i::engine->GetBSPTreeQuery(), mins, maxs, list, listMax);

	const auto entity = info->renderable->GetClientUnknown()->GetBaseEntity();

	if (!entity || !entity->IsPlayer())
		return ListLeavesInBoxOriginal(i::engine->GetBSPTreeQuery(), mins, maxs, list, listMax);

	// No need to reorder teammates
	if (entity->GetTeam() == g::localPlayer->GetTeam())
		return ListLeavesInBoxOriginal(i::engine->GetBSPTreeQuery(), mins, maxs, list, listMax);

	info->flags &= ~RENDER_FLAGS_FORCE_OPAQUE_PASS;
	info->flags2 |= RENDER_FLAGS_BOUNDS_ALWAYS_RECOMPUTE;

	constexpr float maxCoord = 16384.0f;
	constexpr float minCoord = -maxCoord;

	constexpr Vector min{ minCoord, minCoord, minCoord };
	constexpr Vector max{ maxCoord, maxCoord, maxCoord };

	return ListLeavesInBoxOriginal(i::engine->GetBSPTreeQuery(), min, max, list, listMax);
}
