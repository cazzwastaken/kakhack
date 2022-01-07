#include "../hooks.h"

void __stdcall h::LevelInitPostEntity()
{
	LevelInitPostEntityOriginal(i::client);
}
