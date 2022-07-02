#include "hooks.h"

#include "../../external/minhook/minhook.h"
#include <stdexcept>

void h::Setup()
{
	// Populate entity list if already in-game
	g::Setup();

	const auto allocKeyValuesMemory = m::Get(i::keyValues, 1);
	const auto createMove = m::Get(i::clientMode, 24);
	const auto dispatchUserMessage = m::Get(i::client, 38);
	const auto doPostScreenSpaceEffects = m::Get(i::clientMode, 44);
	const auto drawModelExecute = m::Get(i::modelRender, 21);
	const auto endScene = m::Get(i::device, 42);
	const auto frameStageNotify = m::Get(i::client, 37);
	const auto getPlayerMoney = reinterpret_cast<void*>(m::sigs.getPlayerMoney);
	const auto getViewmodelFOV = m::Get(i::clientMode, 35);
	const auto levelInitPostEntity = m::Get(i::client, 6);
	const auto levelInitPreEntity = m::Get(i::client, 5);
	const auto levelShutdown = m::Get(i::client, 7);
	const auto listLeavesInBox = m::Get(i::engine->GetBSPTreeQuery(), 6);
	const auto onScreenSizeChanged = m::Get(i::surface, 116);
	const auto lockCursor = m::Get(i::surface, 67);
	const auto overrideView = m::Get(i::clientMode, 18);
	const auto paint = m::Get(i::engineVGui, 14);
	const auto paintTraverse = m::Get(i::panel, 41);
	const auto reset = m::Get(i::device, 16);
	const auto settingsChatText = reinterpret_cast<void*>(m::sigs.settingsChatText);
	const auto showAlert = reinterpret_cast<void*>(m::sigs.showAlert);
	const auto staticPropInit = reinterpret_cast<void*>(m::sigs.staticPropInit);
	const auto sendDatagram = reinterpret_cast<void*>(m::sigs.sendDatagram);

	if (MH_Initialize())
		throw std::runtime_error("Unable to initialize minhook");

	if (MH_CreateHook(allocKeyValuesMemory, &AllocKeyValuesMemory, reinterpret_cast<void**>(&AllocKeyValuesMemoryOriginal)))
		throw std::runtime_error("Unable to hook AllocKeyValuesMemory()");

	if (MH_CreateHook(createMove, &CreateMove, reinterpret_cast<void**>(&CreateMoveOriginal)))
		throw std::runtime_error("Unable to hook CreateMove()");

	if (MH_CreateHook(dispatchUserMessage, &DispatchUserMessage, reinterpret_cast<void**>(&DispatchUserMessageOriginal)))
		throw std::runtime_error("Unable to hook DispatchUserMessage()");

	if (MH_CreateHook(doPostScreenSpaceEffects, &DoPostScreenSpaceEffects, reinterpret_cast<void**>(&DoPostScreenSpaceEffectsOriginal)))
		throw std::runtime_error("Unable to hook DoPostScreenSpaceEffects()");

	if (MH_CreateHook(drawModelExecute, &DrawModelExecute, reinterpret_cast<void**>(&DrawModelExecuteOriginal)))
		throw std::runtime_error("Unable to hook DrawModelExecute()");

	if (MH_CreateHook(endScene, &EndScene, reinterpret_cast<void**>(&EndSceneOriginal)))
		throw std::runtime_error("Unable to hook EndScene()");

	if (MH_CreateHook(frameStageNotify, &FrameStageNotify, reinterpret_cast<void**>(&FrameStageNotifyOriginal)))
		throw std::runtime_error("Unable to hook FrameStageNotify()");

	if (MH_CreateHook(getPlayerMoney, &GetPlayerMoney, reinterpret_cast<void**>(&GetPlayerMoneyOriginal)))
		throw std::runtime_error("Unable to hook GetPlayerMoney()");

	if (MH_CreateHook(getViewmodelFOV, &GetViewModelFOV, reinterpret_cast<void**>(&GetViewModelFOVOriginal)))
		throw std::runtime_error("Unable to hook GetViewModelFOV()");

	if (MH_CreateHook(levelInitPostEntity, &LevelInitPostEntity, reinterpret_cast<void**>(&LevelInitPostEntityOriginal)))
		throw std::runtime_error("Unable to hook LevelInitPostEntity()");

	if (MH_CreateHook(levelInitPreEntity, &LevelInitPreEntity, reinterpret_cast<void**>(&LevelInitPreEntityOriginal)))
		throw std::runtime_error("Unable to hook levelInitPreEntity()");

	if (MH_CreateHook(levelShutdown, &LevelShutdown, reinterpret_cast<void**>(&LevelShutdownOriginal)))
		throw std::runtime_error("Unable to hook LevelShutdown()");

	if (MH_CreateHook(listLeavesInBox, &ListLeavesInBox, reinterpret_cast<void**>(&ListLeavesInBoxOriginal)))
		throw std::runtime_error("Unable to hook ListLeavesInBox()");

	if (MH_CreateHook(onScreenSizeChanged, &OnScreenSizeChanged, reinterpret_cast<void**>(&OnScreenSizeChangedOriginal)))
		throw std::runtime_error("Unable to hook OnScreenSizeChanged()");

	if (MH_CreateHook(overrideView, &OverrideView, reinterpret_cast<void**>(&OverrideViewOriginal)))
		throw std::runtime_error("Unable to hook OverrideView()");

	if (MH_CreateHook(paint, &Paint, reinterpret_cast<void**>(&PaintOriginal)))
		throw std::runtime_error("Unable to hook Paint()");

	if (MH_CreateHook(paintTraverse, &PaintTraverse, reinterpret_cast<void**>(&PaintTraverseOriginal)))
		throw std::runtime_error("Unable to hook PaintTraverse()");

	if (MH_CreateHook(reset, &Reset, reinterpret_cast<void**>(&ResetOriginal)))
		throw std::runtime_error("Unable to hook Reset()");

	if (MH_CreateHook(settingsChatText, &SettingsChatText, reinterpret_cast<void**>(&SettingsChatTextOriginal)))
		throw std::runtime_error("Unable to hook SettingsChatText()");

	if (MH_CreateHook(showAlert, &ShowAlert, reinterpret_cast<void**>(&ShowAlertOriginal)))
		throw std::runtime_error("Unable to hook ShowAlert()");

	if (MH_CreateHook(staticPropInit, &StaticPropInit, reinterpret_cast<void**>(&StaticPropInitOriginal)))
		throw std::runtime_error("Unable to hook StaticPropInit()");

	if (MH_CreateHook(sendDatagram, &SendDatagram, reinterpret_cast<void**>(&SendDatagramOriginal)))
		throw std::runtime_error("Unable to hook SendDatagram()");

	if (MH_EnableHook(MH_ALL_HOOKS))
		throw std::runtime_error("Unable to enable hooks");

	SequenceOriginal = BaseViewModel::SequenceProp()->proxyFn;
	BaseViewModel::SequenceProp()->proxyFn = Sequence;
}

void h::Destroy() noexcept
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	BaseViewModel::SequenceProp()->proxyFn = SequenceOriginal;
}