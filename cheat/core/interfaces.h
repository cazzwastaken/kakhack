#pragma once
#include <string_view>

#include "globals.h"
#include "variables.h"

#include "../sdk/sdk.h"

struct IDirect3DDevice9;
namespace i
{
	void Setup();

	inline BaseClientDll* client = nullptr;
	inline ClientEntityList* entity = nullptr;
	inline ClientMode* clientMode = nullptr;
	inline DebugOverlay* debug = nullptr;
	inline Effects* effects = nullptr;
	inline EngineClient* engine = nullptr;
	inline EngineConVar* cvar = nullptr;
	inline EngineTrace* trace = nullptr;
	inline EngineVGuiInternal* engineVGui = nullptr;
	inline GameEventManager2* events = nullptr;
	inline GameTypes* gameTypes = nullptr;
	inline GlowObjectManager* glow = nullptr;
	inline Localize* localize = nullptr;
	inline MaterialSystem* materialSystem = nullptr;
	inline ModelInfo* modelInfo = nullptr;
	inline ModelRender* modelRender = nullptr;
	inline Panel* panel = nullptr;
	inline StaticPropManager* staticProps = nullptr;
	inline StudioRender* studio = nullptr;
	inline Surface* surface = nullptr;
	inline ViewRenderBeams* beams = nullptr;
	inline WeaponSystem* weapon = nullptr;
	inline GlobalVarsBase* globals = nullptr;
	inline IDirect3DDevice9* device = nullptr;

	inline Hud* hud = nullptr;
	inline HudChat* hudChat = nullptr;

	inline KeyValues* keyValues = nullptr;
}
