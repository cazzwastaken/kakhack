#include "../hooks.h"

float __stdcall h::GetViewModelFOV()
{
	// Probably should check this
	if (!g::localPlayer)
		return GetViewModelFOVOriginal(i::clientMode);

	// Fucks up with scope
	if (g::localPlayer->IsScoped())
		return GetViewModelFOVOriginal(i::clientMode);

	return v::misc.viewModelFov;
}
