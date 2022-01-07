#include "../hooks.h"

int __stdcall h::DoPostScreenSpaceEffects(const ViewSetup* view)
{
	f::visuals.Glow();

	return DoPostScreenSpaceEffectsOriginal(i::clientMode, view);
}
