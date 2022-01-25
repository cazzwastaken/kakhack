#include <Windows.h>
#include <thread>

#include "core/hooks.h"

// Setup Tree
/*
* Memory [p] -> find patterns
* Interfaces [i] -> Uses patterns from memory namespace
* Netvars [n] -> Uses interfaces
* User Interface [u] -> Uses interfaces
* Hooks [h] -> Uses interfaces & user interface & netvars
*/

void Message(const char* error)
{
	MessageBeep(MB_ICONSTOP);
	MessageBoxA(NULL, error, "kakhack", MB_OK | MB_ICONERROR);
}

void Initialize(HMODULE module)
{
	while (!GetModuleHandle("serverbrowser"))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	try
	{
		m::Setup();
		i::Setup();
		n::Setup();
	}
	catch (const std::exception& e)
	{
		Message(e.what());
		FreeLibraryAndExitThread(module, EXIT_FAILURE);
	}

	g::config.Setup();
	g::render.Setup();

	try
	{
		g::entities.Setup();
		g::events.Setup({"vote_cast", "player_hurt", "player_footstep"});
		u::Setup();
		h::Setup();
	}
	catch (const std::exception& e)
	{
		g::entities.Destroy();
		g::events.Destroy();
		u::Destroy();
		h::Destroy();

		Message(e.what());

		FreeLibraryAndExitThread(module, EXIT_FAILURE);
	}

//#ifdef _DEBUG
	while (!::GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(200));

	h::Destroy();
	u::Destroy();
	g::events.Destroy();
	g::entities.Destroy();

	FreeLibraryAndExitThread(module, EXIT_SUCCESS);
//#endif
}

// entry point
BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID previous)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(instance);

		// create our init thread
		const auto thread = CreateThread(NULL,
			NULL,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(Initialize),
			instance,
			NULL,
			nullptr);

		if (thread)
			CloseHandle(thread);
	}

	return TRUE;
}
