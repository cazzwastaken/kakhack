#include "../hooks.h"

void __stdcall h::OverrideView(ViewSetup* setup)
{
	if (!g::localPlayer)
		return OverrideViewOriginal(i::clientMode, setup);

	if (g::localPlayer->IsScoped())
		return OverrideViewOriginal(i::clientMode, setup);

	setup->fov = v::misc.worldFov;
	OverrideViewOriginal(i::clientMode, setup);
}
