#include "../hooks.h"

void __stdcall h::Paint(int mode)
{
	if (mode & PAINT_UIPANELS)
	{
		i::surface->StartDrawing();

		f::visuals.Renderables();
		f::misc.SniperCrosshair();

		i::surface->FinishDrawing();
	}

	PaintOriginal(i::engineVGui, mode);
}
