#pragma once
#include "../other/config.h"
#include "../other/entities.h"
#include "../other/events.h"
#include "../other/render.h"

class CSPlayer;
class CSPlayerResource;
namespace g
{
	// Init
	void Setup();
	void Shutdown();

	// Utils
	// Log to in-game console
	void Log(const char* format, ...);

	// Context Pointers
	inline CSPlayer* localPlayer = nullptr;
	inline CSPlayerResource* resource = nullptr;

	inline struct Screen
	{
		int x, y;
	}screen;

	// Global Objects
	inline auto config = Config{ };
	inline auto entities = EntityListener{ };
	inline auto events = EventListener{ };
	inline auto render = Render{ };
}
