#include "../hooks.h"

#include "../../../external/imgui/imgui_impl_dx9.h"

HRESULT __stdcall h::Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentationParameters)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	const auto result = ResetOriginal(device, device, presentationParameters);
	ImGui_ImplDX9_CreateDeviceObjects();

	return result;
}
