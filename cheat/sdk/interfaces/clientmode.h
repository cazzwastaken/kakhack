#pragma once
#include "../definitions.h"

#include "../data/vector.h"
#include "../classes/usercmd.h"

#include "panel.h"

class ViewSetup
{
public:
	int			x;
	int			unscaledX;
	int			y;
	int			unscaledY;
	int			width;
	int			unscaledWidth;
	int			height;
	int			unscaledHeight;
	bool		ortho;
	float		orthoLeft;
	float		orthoTop;
	float		orthoRight;
	float		orthoBottom;
	std::byte	pad0[0x7C];
	float		fov;
	float		viewModelFOV;
	Vector		origin;
	Vector		view;
	float		nearZ;
	float		farZ;
	float		nearViewmodelZ;
	float		farViewmodelZ;
	float		aspectRatio;
	float		nearBlurDepth;
	float		nearFocusDepth;
	float		farFocusDepth;
	float		farBlurDepth;
	float		nearBlurRadius;
	float		farBlurRadius;
	float		doFQuality;
	int			motionBlurMode;
	float		shutterTime;
	Vector		shutterOpenPosition;
	Vector		shutterOpenAngles;
	Vector		shutterClosePosition;
	Vector		shutterCloseAngles;
	float		offCenterTop;
	float		offCenterBottom;
	float		offCenterLeft;
	float		offCenterRight;
	bool		offCenter : 1;
	bool		renderToSubrectOfLargerScreen : 1;
	bool		bloomAndToneMapping : 1;
	bool		depthOfField : 1;
	bool		HDRTarget : 1;
	bool		drawWorldNormal : 1;
	bool		cullFontFaces : 1;
	bool		cacheFullSceneState : 1;
	bool		CSMView : 1;
};

class AnimationController;
struct AudioState;

class ClientMode
{
public:
	virtual			~ClientMode() {}

	// Called before the HUD is initialized.
	virtual void	InitViewport() = 0;

	// One time init when .dll is first loaded.
	virtual void	Init() = 0;

	// Called when vgui is shutting down.
	virtual void	VGui_Shutdown() = 0;

	// One time call when dll is shutting down
	virtual void	Shutdown() = 0;

	// Called when switching from one IClientMode to another.
	// This can re-layout the view and such.
	// Note that Enable and Disable are called when the DLL initializes and shuts down.
	virtual void	Enable() = 0;
	virtual void	EnableWithRootPanel(VPANEL pRoot) = 0;

	// Called when it's about to go into another client mode.
	virtual void	Disable() = 0;

	// Called when initializing or when the view changes.
	// This should move the viewport into the correct position.
	virtual void	Layout(bool bForce = false) = 0;

	// Gets at the viewport, if there is one...
	virtual Panel* GetViewport() = 0;

	// Gets a panel hierarchically below the viewport by name like so "ASWHudInventoryMode/SuitAbilityPanel/ItemPanel1"...
	virtual Panel* GetPanelFromViewport(const char* pchNamePath) = 0;

	// Gets at the viewports vgui panel animation controller, if there is one...
	virtual AnimationController* GetViewportAnimationController() = 0;

	// called every time shared client dll/engine data gets changed,
	// and gives the cdll a chance to modify the data.
	virtual void	ProcessInput(bool bActive) = 0;

	// The mode can choose to draw/not draw entities.
	virtual bool	ShouldDrawDetailObjects() = 0;
	virtual bool	ShouldDrawEntity(BaseEntity* pEnt) = 0;
	virtual bool	ShouldDrawLocalPlayer(BasePlayer* pPlayer) = 0;
	virtual bool	ShouldDrawParticles() = 0;

	// The mode can choose to not draw fog
	virtual bool	ShouldDrawFog(void) = 0;

	virtual void	OverrideView(ViewSetup* pSetup) = 0;
	virtual void	OverrideAudioState(AudioState* pAudioState) = 0;
	virtual int		KeyInput(int down, ButtonCode keynum, const char* pszCurrentBinding) = 0;
	virtual void	StartMessageMode(int iMessageModeType) = 0;
	virtual Panel* GetMessagePanel() = 0;
	virtual void	OverrideMouseInput(float* x, float* y) = 0;
	virtual bool	CreateMove(float flInputSampleTime, UserCmd* cmd) = 0;

	virtual void	LevelInit(const char* newmap) = 0;
	virtual void	LevelShutdown(void) = 0;

	// Certain modes hide the view model
	virtual bool	ShouldDrawViewModel(void) = 0;
	virtual bool	ShouldDrawCrosshair(void) = 0;

	// Let mode override viewport for engine
	virtual void	AdjustEngineViewport(int& x, int& y, int& width, int& height) = 0;

	// Called before rendering a view.
	virtual void	PreRender(ViewSetup* pSetup) = 0;

	// Called after everything is rendered.
	virtual void	PostRender(void) = 0;

	virtual void	PostRenderVGui() = 0;

	virtual void	ActivateInGameVGuiContext(Panel* pPanel) = 0;
	virtual void	DeactivateInGameVGuiContext() = 0;
	virtual float	GetViewModelFOV(void) = 0;

	virtual bool	CanRecordDemo(char* errorMsg, int length) const = 0;

	virtual wchar_t* GetServerName(void) = 0;
	virtual void		SetServerName(wchar_t* name) = 0;
	virtual wchar_t* GetMapName(void) = 0;
	virtual void		SetMapName(wchar_t* name) = 0;

	virtual void	OnColorCorrectionWeightsReset(void) = 0;
	virtual float	GetColorCorrectionScale(void) const = 0;

	virtual int		HudElementKeyInput(int down, ButtonCode keynum, const char* pszCurrentBinding) = 0;

	virtual void	DoPostScreenSpaceEffects(const ViewSetup* pSetup) = 0;

	virtual void	UpdateCameraManUIState(int iType, int nOptionalParam, uint64_t xuid) = 0;
	virtual void	ScoreboardOff(void) = 0;
	virtual void	GraphPageChanged(void) = 0;

	// Called every frame.
	virtual void	Update() = 0;

	virtual void	SetBlurFade(float scale) = 0;
	virtual float	GetBlurFade(void) = 0;
};
