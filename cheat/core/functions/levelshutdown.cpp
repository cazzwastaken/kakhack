#include "../hooks.h"

void __stdcall h::LevelShutdown()
{
	g::Shutdown();

	return LevelShutdownOriginal(i::client);
}
