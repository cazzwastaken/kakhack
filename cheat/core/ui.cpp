#include "ui.h"

#include <Windows.h>
#include <stdexcept>

#include "../../external/imgui/imgui.h"
#include "../../external/imgui/imgui_impl_dx9.h"
#include "../../external/imgui/imgui_impl_win32.h"

LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM wideParam, LPARAM longParam);

void u::Setup()
{
	auto creationParams = D3DDEVICE_CREATION_PARAMETERS{ };
	if (FAILED(i::device->GetCreationParameters(&creationParams)))
	{
		throw std::runtime_error("Failed to get device creation parameters");
	}

	window = creationParams.hFocusWindow;
	WindowProcessOriginal = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(window,
		GWLP_WNDPROC,
		reinterpret_cast<LONG_PTR>(WindowProcess)));

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowPadding = { 15, 15 };
	style->WindowRounding = 0.f;
	style->WindowTitleAlign = { 0.5f, 0.5f };
	style->WindowBorderSize = 1;

	style->FrameRounding = 0.f;
	style->FramePadding = { 20, 7 };
	style->FrameBorderSize = 1;

	style->ChildRounding = 0.f;

	style->ScrollbarSize = 3.f;
	style->ScrollbarRounding = 1.f;

	style->ItemSpacing = { 8, 8 };

	style->TabRounding = 0.f;

	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 0.96f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.11f, 0.11f, 0.14f, 1.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.32f, 0.32f, 0.58f, 0.30f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.17f, 0.00f, 0.52f, 0.26f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.27f, 0.38f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.29f, 0.37f, 0.62f, 0.54f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.33f, 0.33f, 0.67f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.33f, 0.33f, 0.68f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.33f, 0.33f, 0.67f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.81f, 0.66f, 1.00f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Button] = ImVec4(0.35f, 0.37f, 0.48f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.33f, 0.35f, 0.49f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.33f, 0.33f, 0.67f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.42f, 0.32f, 0.67f, 1.00f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.50f, 0.41f, 0.73f, 1.00f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.33f, 0.33f, 0.67f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImVec4(0.58f, 0.50f, 1.00f, 0.35f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.38f, 0.29f, 0.84f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.33f, 0.24f, 0.80f, 1.00f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(i::device);

	segoe = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\segoeui.ttf", 15.f);

	ImGui::SetColorEditOptions(ImGuiColorEditFlags_NoInputs
		| ImGuiColorEditFlags_NoLabel
		| ImGuiColorEditFlags_NoSidePreview
		| ImGuiColorEditFlags_Uint8
		| ImGuiColorEditFlags_AlphaBar);
}

void u::Destroy()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	SetWindowLongPtrW(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProcessOriginal));
}

#define VISUALS_COLOR_BOOL(name) \
ImGui::Checkbox(#name, &v::visuals.name.first); \
ImGui::SameLine(offset); \
ImGui::ColorEdit4(#name, v::visuals.name.second.data())

#define MISC_COLOR_BOOL(name) \
ImGui::Checkbox(#name, &v::misc.name.first); \
ImGui::SameLine(offset); \
ImGui::ColorEdit4(#name, v::misc.name.second.data())

void HelpMarker(const char* desc)
{
	ImGui::SameLine();
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void u::Render()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::PushFont(segoe);
	ImGui::SetNextWindowSize({ 512, 500 });
	ImGui::Begin("kakhack v1", &open,
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings //|
	/*ImGuiWindowFlags_NoTitleBar*/);

	static auto tab = 0;

	const auto tabSize = ImVec2(90, 40);
	if (ImGui::Button("aimbot", tabSize)) { tab = 0; }
	ImGui::SameLine();
	if (ImGui::Button("visuals", tabSize)) { tab = 1; }
	ImGui::SameLine();
	if (ImGui::Button("misc", tabSize)) { tab = 2; }
	ImGui::SameLine();
	if (ImGui::Button("skins", tabSize)) { tab = 3; }
	ImGui::SameLine();
	if (ImGui::Button("config", tabSize)) { tab = 4; }

	const auto avail = ImGui::GetContentRegionAvail();
	const auto offset = 195.f;

	switch (tab)
	{
	case 0:
		ImGui::BeginChild(1, { }, true);
		ImGui::EndChild();

		break;
	case 1:
		ImGui::BeginGroup();
		ImGui::BeginChild(1, { (avail.x - 8) * 0.5f, avail.y * 0.65f }, true);
		ImGui::Text("Renderables:");
		HelpMarker("Shit that gets rendered");
		ImGui::Separator();
		ImGui::Spacing();
		VISUALS_COLOR_BOOL(box);
		VISUALS_COLOR_BOOL(filled);
		VISUALS_COLOR_BOOL(outlined);
		VISUALS_COLOR_BOOL(name);
		VISUALS_COLOR_BOOL(headdot);
		ImGui::EndChild();

		ImGui::BeginChild(2, { (avail.x - 8) * 0.5f, ImGui::GetContentRegionAvail().y }, true);
		ImGui::Text("World Colors:");
		HelpMarker("Change before map load to save you sweet fps");
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Text("world");
		ImGui::SameLine(offset);
		ImGui::ColorEdit4("world", v::visuals.world.data());
		ImGui::Text("props");
		ImGui::SameLine(offset);
		ImGui::ColorEdit4("props", v::visuals.props.data());
		ImGui::Text("sky");
		ImGui::SameLine(offset);
		ImGui::ColorEdit4("sky", v::visuals.sky.data());
		ImGui::EndChild();
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::BeginChild(3, { (avail.x - 8) * 0.5f, (avail.y - 8) * 0.5f }, true);
		ImGui::Text("Colored Models:");
		HelpMarker("Also known as chams");
		ImGui::Separator();
		VISUALS_COLOR_BOOL(visible);
		VISUALS_COLOR_BOOL(hidden);
		VISUALS_COLOR_BOOL(item);
		VISUALS_COLOR_BOOL(arm);
		VISUALS_COLOR_BOOL(sleeve);
		ImGui::EndChild();

		ImGui::BeginChild(4, { }, true);
		ImGui::Text("Glow:");
		HelpMarker("Force glow on entities");
		ImGui::Separator();
		VISUALS_COLOR_BOOL(player);
		VISUALS_COLOR_BOOL(weapon);
		VISUALS_COLOR_BOOL(grenade);
		VISUALS_COLOR_BOOL(bomb);
		VISUALS_COLOR_BOOL(chicken);
		ImGui::Spacing();

		ImGui::EndChild();
		ImGui::EndGroup();
		break;
	case 2:
		ImGui::BeginGroup();
		ImGui::BeginChild(1, { (avail.x - 8) * 0.5f, (avail.y * 0.4f) }, true);
		ImGui::Text("Revealers:");
		HelpMarker("Reveal the shit you aren't supposed to see");
		ImGui::Separator();
		ImGui::Checkbox("ranks", &v::misc.ranks);
		ImGui::Checkbox("radar", &v::misc.radar);
		ImGui::Checkbox("votes", &v::misc.votes);
		ImGui::Checkbox("money", &v::misc.money);
		ImGui::EndChild();

		ImGui::BeginChild(2, { (avail.x - 8) * 0.5f, (avail.y * 0.33f) }, true);
		ImGui::Text("Field of View:");
		HelpMarker("Fuck with your fov");
		ImGui::Separator();
		ImGui::SliderFloat("viewmodel", &v::misc.viewModelFov, 0.1f, 200.0f, "%.1f fov");
		ImGui::SliderFloat("world", &v::misc.worldFov, 0.1f, 200.0f, "%.1f fov");
		ImGui::EndChild();

		ImGui::BeginChild(3, { (avail.x - 8) * 0.5f, ImGui::GetContentRegionAvail().y }, true);
		ImGui::Text("Movement:");
		HelpMarker("Look better ;)");
		ImGui::Separator();
		ImGui::Checkbox("bunnyhop", &v::misc.bunnyHop);
		ImGui::EndChild();
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::BeginChild(4, { (avail.x - 8) * 0.5f, 0.3f }, true);
		ImGui::Text("Visuals:");
		HelpMarker("Misc visuals dude");
		ImGui::Separator();
		MISC_COLOR_BOOL(sniperCrosshair);
		MISC_COLOR_BOOL(hitMarker);
		MISC_COLOR_BOOL(hitEffect);
		MISC_COLOR_BOOL(stepEffect);
		ImGui::EndChild();
		ImGui::EndGroup();
		break;
	case 3:
	{
		ImGui::BeginGroup();
		ImGui::BeginChild(1, { (avail.x - 8) * 0.5f, avail.y }, true);
		ImGui::Text("Skins:");
		HelpMarker("Weapons with skins being applied");
		ImGui::Separator();

		ImGui::EndChild();
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::BeginChild(2, { (avail.x - 8) * 0.5f, avail.y }, true);
		ImGui::Text("Customizer:");
		HelpMarker("Options for selected config");
		ImGui::Separator();

		ImGui::EndChild();
		ImGui::EndGroup();
	}break;
	case 4:
	{
		ImGui::BeginGroup();
		ImGui::BeginChild(1, { (avail.x - 8) * 0.5f, avail.y }, true);
		ImGui::Text("Configs:");
		HelpMarker("Saved in csgo_dir/kakhack/configs");
		ImGui::Separator();

		style->FramePadding = { 20, 20 };
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth());
		if (ImGui::BeginListBox("##config_box", { ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y * 0.85f }))
		{
			for (size_t i = 0; i < g::config.Size(); ++i)
			{
				const bool isSelected = (g::config.Selected() == i);

				if (ImGui::Selectable(g::config[i], isSelected))
					g::config.Selected() = i;

				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndListBox();
		}
		style->FramePadding = { 20, 7 };

		if (ImGui::Button("refresh", { ImGui::GetContentRegionAvail() }))
			g::config.Refresh();
		ImGui::EndChild();
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		ImGui::BeginChild(2, { (avail.x - 8) * 0.5f, (avail.y - 8) * 0.72f }, true);
		ImGui::Text("Selected:");
		ImGui::SameLine();
		ImGui::TextDisabled("%s", g::config.GetSelectedName());
		HelpMarker("Options for selected config");
		ImGui::Separator();

		const auto size = ImVec2(ImGui::GetContentRegionAvailWidth(), 34);

		if (ImGui::Button("save", size))
			g::config.Save();
		if (ImGui::Button("load", size))
			g::config.Load();
		ImGui::Spacing();
		ImGui::SetNextItemWidth(ImGui::GetContentRegionAvailWidth());
		ImGui::InputTextWithHint("##config_name",
			"config name",
			g::config.nameBuffer,
			IM_ARRAYSIZE(g::config.nameBuffer),
			ImGuiInputTextFlags_CharsNoBlank);
		if (ImGui::Button("create", size))
			g::config.Create();
		ImGui::Spacing();
		if (ImGui::Button("delete", size))
			g::config.Delete();
		ImGui::EndChild();

		ImGui::BeginChild(3, { }, true);

		ImGui::Text("Info:");
		ImGui::Separator();
		ImGui::Text("version:");
		ImGui::SameLine();
		ImGui::TextDisabled("v1.0 beta");
		ImGui::Text("author:");
		ImGui::SameLine();
		ImGui::TextDisabled("cazz");

		ImGui::EndChild();
		ImGui::EndGroup();
	}break;
	}

	ImGui::End();
	ImGui::PopFont();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND window, UINT message, WPARAM wideParam, LPARAM longParam);
LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM wideParam, LPARAM longParam)
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		u::open = !u::open;

	if (u::open && ImGui_ImplWin32_WndProcHandler(window, message, wideParam, longParam))
		return 1L;

	return CallWindowProc(u::WindowProcessOriginal, window, message, wideParam, longParam);
}
