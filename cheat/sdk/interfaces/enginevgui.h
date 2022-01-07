#pragma once
#include "../definitions.h"

DECLARE_POINTER_HANDLE(InputContextHandle);
struct InputEvent;

enum VGuiPanel
{
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

enum PaintMode
{
	PAINT_UIPANELS = (1 << 0),
	PAINT_INGAMEPANELS = (1 << 1),
	PAINT_CURSOR = (1 << 2)
};

enum LevelLoadingProgress
{
	PROGRESS_INVALID = -2,
	PROGRESS_DEFAULT = -1,

	PROGRESS_NONE,
	PROGRESS_CHANGELEVEL,
	PROGRESS_SPAWNSERVER,
	PROGRESS_LOADWORLDMODEL,
	PROGRESS_CRCMAP,
	PROGRESS_CRCCLIENTDLL,
	PROGRESS_CREATENETWORKSTRINGTABLES,
	PROGRESS_PRECACHEWORLD,
	PROGRESS_CLEARWORLD,
	PROGRESS_LEVELINIT,
	PROGRESS_PRECACHE,
	PROGRESS_ACTIVATESERVER,
	PROGRESS_BEGINCONNECT,
	PROGRESS_SIGNONCHALLENGE,
	PROGRESS_SIGNONCONNECT,
	PROGRESS_SIGNONCONNECTED,
	PROGRESS_PROCESSSERVERINFO,
	PROGRESS_PROCESSSTRINGTABLE,
	PROGRESS_SIGNONNEW,
	PROGRESS_SENDCLIENTINFO,
	PROGRESS_SENDSIGNONDATA,
	PROGRESS_SIGNONSPAWN,
	PROGRESS_CREATEENTITIES,
	PROGRESS_FULLYCONNECTED,
	PROGRESS_PRECACHELIGHTING,
	PROGRESS_READYTOPLAY,
	PROGRESS_HIGHESTITEM,	// must be last item in list
};

class EngineVGui
{
public:
	virtual			~EngineVGui() { }
	virtual VPANEL	GetPanel(VGuiPanel type) = 0;
	virtual bool	IsGameUIVisible() = 0;
	virtual void			ActivateGameUI() = 0;
};

class EngineVGuiInternal : public EngineVGui
{
public:
	virtual void Init() = 0;
	virtual void Connect() = 0;
	virtual void Shutdown() = 0;
	virtual bool SetVGUIDirectories() = 0;
	virtual bool IsInitialized() const = 0;
	virtual CreateInterfaceFn GetGameUIFactory() = 0;
	virtual bool Key_Event(const InputEvent& event) = 0;
	virtual void BackwardCompatibility_Paint() = 0;
	virtual void UpdateButtonState(const InputEvent& event) = 0;
	virtual void PostInit() = 0;

	virtual void Paint(PaintMode mode) = 0; // 14

	// handlers for game UI (main menu)
	virtual bool HideGameUI() = 0;

	// console
	virtual void ShowConsole() = 0;
	virtual void HideConsole() = 0;
	virtual bool IsConsoleVisible() = 0;
	virtual void ClearConsole() = 0;

	virtual void nullsub_1() = 0;

	// level loading
	virtual void OnLevelLoadingStarted(const char* levelName, bool bLocalServer) = 0;
	virtual void OnLevelLoadingFinished() = 0;
	virtual void NotifyOfServerConnect(const char* game, int IP, int connectionPort, int queryPort) = 0;
	virtual void NotifyOfServerDisconnect() = 0;
	virtual void EnabledProgressBarForNextLoad() = 0;
	virtual void UpdateProgressBar(LevelLoadingProgress progress, bool showDialog = true) = 0;
	virtual void UpdateCustomProgressBar(float progress, const wchar_t* desc) = 0;
	virtual void StartCustomProgress() = 0;
	virtual void FinishCustomProgress() = 0;
	virtual void UpdateSecondaryProgressBarWithFile(float progress, const char* desc, int bytesTotal) = 0;
	virtual void UpdateSecondaryProgressBar(float progress, const wchar_t* desc) = 0;
	virtual void ShowErrorMessage() = 0;
	virtual void HideLoadingPlaque() = 0;
	virtual void StartLoadingScreenForCommand(const char* command) = 0;
	virtual void StartLoadingScreenForKeyValues(KeyValues* keyValues) = 0;

	// Should pause?
	virtual bool ShouldPause() = 0;
	virtual void SetGameDLLPanelsVisible(bool show) = 0;

	virtual void nullsub_2() = 0;

	virtual void Simulate() = 0;

	virtual void SetNotAllowedToHideGameUI(bool bNotAllowedToHide) = 0;
	virtual void SetNotAllowedToShowGameUI(bool bNotAllowedToShow) = 0;

	virtual void NeedConnectionProblemWaitScreen() = 0;

	virtual void nullsub_3() = 0;

	virtual void OnToolModeChanged(bool bGameMode) = 0;

	virtual InputContextHandle GetGameUIInputContext() = 0;

	virtual bool IsPlayingFullScreenVideo() = 0;
};
