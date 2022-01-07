#include "../hooks.h"

void __stdcall h::OnScreenSizeChanged(int oldHeight, int oldWidth)
{
	i::surface->GetScreenSize(g::screen.x, g::screen.y);
	i::surface->ResetFontCaches();

	return OnScreenSizeChangedOriginal(i::surface, oldHeight, oldWidth);
}
