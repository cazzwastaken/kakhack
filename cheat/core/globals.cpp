#include "globals.h"
#include "interfaces.h"

void g::Setup()
{
	i::surface->GetScreenSize(g::screen.x, g::screen.y);

	if (!i::engine->IsInGame())
	{
		return;
	}

	g::entities.Update();
}

void g::Shutdown()
{
	localPlayer = nullptr;
	resource = nullptr;
}

void g::Log(const char* format, ...)
{
	i::cvar->ConsoleColorPrintf({ 255, 0, 255 }, "[kh] ");
	i::cvar->ConsolePrintf(format);
}
