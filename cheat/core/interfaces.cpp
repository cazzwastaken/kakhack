#include "interfaces.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdexcept>
#include <format>

template <typename T>
static T* Get(const char* module, std::string_view version)
{
	const auto handle = GetModuleHandle(module);

	if (!handle)
	{
		throw std::runtime_error(std::format("Failed to get \"{}\" module handle.", module));
	}

	const auto createInterface = reinterpret_cast<uintptr_t>(GetProcAddress(handle, "CreateInterface"));

	if (!createInterface)
	{
		throw std::runtime_error(std::format("Failed to get CreateInterface in \"{}\".", module));
	}

	const auto relative = createInterface + 5;
	const auto address = m::RelativeToAbsolute(relative);
	const auto interfaces = **reinterpret_cast<InterfaceRegister***>(address + 6);

	if (!interfaces)
	{
		throw std::runtime_error(std::format("Failed to get s_pInterfaceRegs in \"{}\".", module));
	}

	for (auto item = interfaces; item; item = item->next)
	{
		if ((!std::string_view(item->name).compare(0U, version.length(), version) &&
			std::atoi(item->name + version.length()) > 0) ||
			!version.compare(item->name))
		{
			const auto pointer = item->CreateInterface();

			if (!pointer)
			{
				throw std::runtime_error(std::format("Failed to create \"{}\"", item->name));
			}

			return static_cast<T*>(pointer);
		}
	}

	throw std::runtime_error(std::format("Failed to find {} in {}", version, module));
}

void i::Setup()
{
	client = Get<BaseClientDll>("client", "VClient");
	entity = Get<ClientEntityList>("client", "VClientEntityList");
	debug = Get<DebugOverlay>("engine", "VDebugOverlay");

	if (!(clientMode = **reinterpret_cast<ClientMode***>((*reinterpret_cast<uintptr_t**>(client))[10] + 5)))
	{
		throw std::runtime_error("Unable to get ClientMode pointer.");
	}

	effects = Get<Effects>("client", "IEffects");
	engine = Get<EngineClient>("engine", "VEngineClient");
	cvar = Get<EngineConVar>("vstdlib", "VEngineCvar");
	trace = Get<EngineTrace>("engine", "EngineTraceClient");
	engineVGui = Get<EngineVGuiInternal>("engine", "VEngineVGui");
	events = Get<GameEventManager2>("engine", "GAMEEVENTSMANAGER002");
	gameTypes = Get<GameTypes>("matchmaking", "VENGINE_GAMETYPES_VERSION");
	glow = *reinterpret_cast<GlowObjectManager**>(m::sigs.glowObjectManager);
	localize = Get<Localize>("localize", "Localize_");
	materialSystem = Get<MaterialSystem>("materialsystem", "VMaterialSystem");
	modelInfo = Get<ModelInfo>("engine", "VModelInfoClient");
	modelRender = Get<ModelRender>("engine", "VEngineModel");
	panel = Get<Panel>("vgui2", "VGUI_Panel");
	staticProps = Get<StaticPropManager>("engine", "StaticPropMgrClient");
	studio = Get<StudioRender>("studiorender", "VStudioRender");
	surface = Get<Surface>("vguimatsurface", "VGUI_Surface");
	beams = *reinterpret_cast<ViewRenderBeams**>(m::sigs.viewRenderBeams);
	weapon = *reinterpret_cast<WeaponSystem**>(m::sigs.weaponSystem);
	device = **reinterpret_cast<IDirect3DDevice9***>(m::sigs.device);

	if (!(globals = **reinterpret_cast<GlobalVarsBase***>((*reinterpret_cast<uintptr_t**>(client))[11] + 10)))
	{
		throw std::runtime_error("Unable to get GlobalVars pointer.");
	}

	hud = *reinterpret_cast<Hud**>(m::sigs.hud);
	hudChat = hud->FindElement<HudChat>("CHudChat");

	const auto vstdlib = GetModuleHandle("vstdlib");

	if (!vstdlib)
	{
		throw std::runtime_error("Unable to get handle to vstdlib.dll.");
	}

	keyValues = reinterpret_cast<KeyValuesSystemFn>(GetProcAddress(vstdlib, "KeyValuesSystem"))();

	if (!keyValues)
	{
		throw std::runtime_error("Unable to get KeyValuesSystem pointer.");
	}
}
