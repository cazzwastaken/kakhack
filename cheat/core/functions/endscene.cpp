#include "../hooks.h"

#include <intrin.h>

#include "../../../external/imgui/imgui.h"
#include "../../../external/imgui/imgui_impl_dx9.h"
#include "../../../external/imgui/imgui_impl_win32.h"

long __stdcall h::EndScene(IDirect3DDevice9* device)
{
	static const auto returnAddress = _ReturnAddress();

	const auto result = h::EndSceneOriginal(device, device);

	// EndScene gets called twice
	if (_ReturnAddress() == returnAddress)
		return result;

	if (u::open)
		u::Render();

	return result;
}
