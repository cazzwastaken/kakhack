#include "../hooks.h"

void __stdcall h::PaintTraverse(VPANEL panel, bool forceRepaint, bool allowForce)
{
	// Find a better way of doing this? This doesn't need to be called each frame...
	if (fnv::Hash(i::panel->GetName(panel)) == fnv::HashConst("FocusOverlayPanel"))
	{
		i::panel->SetKeyBoardInputEnabled(panel, u::open);
		i::panel->SetMouseInputEnabled(panel, u::open);
	}

	PaintTraverseOriginal(i::panel, panel, forceRepaint, allowForce);
}
