#pragma once

#include "ui.h"

namespace h
{
	// Place & enable all hooks at once
	void Setup();

	// Destroy hooks for uninjection
	void Destroy() noexcept;

	using AllocKeyValuesMemoryFn = void*(__thiscall*)(void*, int);
	inline AllocKeyValuesMemoryFn AllocKeyValuesMemoryOriginal = { nullptr };
	void* __stdcall AllocKeyValuesMemory(int size);

	using CreateMoveFn = bool(__thiscall*)(void*, float, UserCmd*);
	inline CreateMoveFn CreateMoveOriginal = { nullptr };
	bool __stdcall CreateMove(float frameTime, UserCmd* cmd);

	using DispatchUserMessageFn = int(__thiscall*)(void*, int, uint32_t, int, const void*);
	inline DispatchUserMessageFn DispatchUserMessageOriginal = { nullptr };
	bool __stdcall DispatchUserMessage(int type, uint32_t flags, int size, const void* message);

	using DoPostScreenSpaceEffectsFn = int(__thiscall*)(void*, const ViewSetup*);
	inline DoPostScreenSpaceEffectsFn DoPostScreenSpaceEffectsOriginal = { nullptr };
	int __stdcall DoPostScreenSpaceEffects(const ViewSetup* view);

	using DrawModelExecuteFn = void(__thiscall*)(void*, MatRenderContext*, const DrawModelState&, const ModelRenderInfo&, Matrix3x4*);
	inline DrawModelExecuteFn DrawModelExecuteOriginal = { nullptr };
	void __stdcall DrawModelExecute(MatRenderContext* context, const DrawModelState& state, const ModelRenderInfo& info, Matrix3x4* customBoneToWorld);

	using EndSceneFn = long(__thiscall*)(void*, IDirect3DDevice9*);
	inline EndSceneFn EndSceneOriginal = { nullptr };
	long __stdcall EndScene(IDirect3DDevice9* device);

	using FrameStageNotifyFn = void(__thiscall*)(void*, ClientFrameStage);
	inline FrameStageNotifyFn FrameStageNotifyOriginal = { nullptr };
	void __stdcall FrameStageNotify(ClientFrameStage stage);

	using GetPlayerMoneyFn = int(__thiscall*)(void*, int);
	inline GetPlayerMoneyFn GetPlayerMoneyOriginal = { nullptr };
	int __fastcall GetPlayerMoney(void* thisptr, void* edx, int entityIndex);

	using GetViewModelFOVFn = float(__thiscall*)(void*);
	inline GetViewModelFOVFn GetViewModelFOVOriginal = { nullptr };
	float __stdcall GetViewModelFOV();

	using LevelInitPostEntityFn = void(__thiscall*)(void*);
	inline LevelInitPostEntityFn LevelInitPostEntityOriginal = { nullptr };
	void __stdcall LevelInitPostEntity();

	using LevelInitPreEntityFn = void(__thiscall*)(void*, const char*);
	inline LevelInitPreEntityFn LevelInitPreEntityOriginal = { nullptr };
	void __stdcall LevelInitPreEntity(const char* mapName);

	using LevelShutdownFn = void(__thiscall*)(void*);
	inline LevelShutdownFn LevelShutdownOriginal = { nullptr };
	void __stdcall LevelShutdown();

	using ListLeavesInBoxFn = int(__thiscall*)(void*, const Vector&, const Vector&, unsigned short*, int);
	inline ListLeavesInBoxFn ListLeavesInBoxOriginal = { nullptr };
	int __stdcall ListLeavesInBox(const Vector& mins, const Vector& maxs, unsigned short* list, int listMax);

	using OnScreenSizeChangedFn = void(__thiscall*)(void*, int, int);
	inline OnScreenSizeChangedFn OnScreenSizeChangedOriginal = { nullptr };
	void __stdcall OnScreenSizeChanged(int oldHeight, int oldWidth);

	using OverrideViewFn = void(__thiscall*)(void*, ViewSetup*);
	inline OverrideViewFn OverrideViewOriginal = { nullptr };
	void __stdcall OverrideView(ViewSetup* setup);

	using PaintFn = void(__thiscall*)(void*, int);
	inline PaintFn PaintOriginal = { nullptr };
	void __stdcall Paint(int mode);

	using PaintTraverseFn = void(__thiscall*)(void*, unsigned int, bool, bool);
	inline PaintTraverseFn PaintTraverseOriginal = { nullptr };
	void __stdcall PaintTraverse(VPANEL panel, bool forceRepaint, bool allowForce);

	using ResetFn = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
	inline ResetFn ResetOriginal = { nullptr };
	HRESULT __stdcall Reset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentationParameters);

	using SettingsChatTextFn = void(__thiscall*)(void*, const char*);
	inline SettingsChatTextFn SettingsChatTextOriginal = { nullptr };
	void __fastcall SettingsChatText(void* thisptr, void* edx, const char* text);

	using ShowAlertFn = void(__thiscall*)(void*, const char*, int);
	inline ShowAlertFn ShowAlertOriginal = { nullptr };
	void __fastcall ShowAlert(void* thisptr, void* edx, const char* text, int mode);

	using StaticPropInitFn = bool(__thiscall*)(StaticProp*, int, StaticPropLump&, Model*);
	inline StaticPropInitFn StaticPropInitOriginal = { nullptr };
	bool __fastcall StaticPropInit(StaticProp* thisptr, void* edx, int index, StaticPropLump& lump, Model* model);

	using SendDatagramFn = int(__fastcall*)(NetChannel*, int, bf_write*);
	inline SendDatagramFn SendDatagramOriginal = { nullptr };
	int __fastcall SendDatagram(NetChannel* thisptr, int edx, bf_write* datagram);

	// Proxies
	inline RecvVarProxyFn SequenceOriginal = { nullptr };
	void __cdecl Sequence(const RecvProxyData* data, void* entity, void* output);
}
