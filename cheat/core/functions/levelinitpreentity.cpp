#include "../hooks.h"

void __stdcall h::LevelInitPreEntity(const char* mapName)
{
	// Color the world and shit g
	f::visuals.WorldColor();

	LevelInitPreEntityOriginal(i::client, mapName);
}
