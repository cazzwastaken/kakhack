#pragma once
#include "gameeventmanager.h"

class Hud
{
public:
	template <typename T>
	T* FindElement(const char* name)
	{
		using FindElementFn = T * (__thiscall*)(void*, const char*);
		static const auto Function = reinterpret_cast<FindElementFn>(m::sigs.findElement);
		return Function(this, name);
	}
};

class HudElement : public GameEventListener2
{
public:

	virtual void				SetHud(Hud* pHud) = 0;

	// called when the Hud is initialised (whenever the DLL is loaded)
	virtual void				Init(void) = 0;

	// called whenever the video mode changes, and whenever Init() would be called, so the hud can vid init itself
	virtual void				VidInit(void) = 0;

	// LevelInit's called whenever a new level's starting
	virtual void				LevelInit(void) = 0;
	// LevelShutdown's called whenever a level's finishing
	virtual void				LevelShutdown(void) = 0;

	// called whenever the hud receives "reset" message, which is (usually) every time the client respawns after getting killed
	virtual void				Reset(void) = 0;

	// Called once per frame for visible elements before general key processing
	virtual void				ProcessInput(void) = 0;

	// Called once per frame whether the element is visible or not
	virtual void				Think(void) = 0;

	// Called when time warping occurs, i.e. when instant replay rewinds or forwards client's time
	virtual void				OnTimeJump(void) = 0;

	//
	virtual const char* GetName(void) const = 0;

	// Return true if this hud element should be visible in the current hud state
	virtual bool				ShouldDraw(void) = 0;

	virtual bool				IsActive(void) = 0;
	virtual void				SetActive(bool bActive) = 0;

	// Hidden bits.
	// HIDEHUD_ flags that note when this element should be hidden in the HUD
	virtual void				SetHiddenBits(int iBits) = 0;

	virtual void				SetIgnoreGlobalHudDisable(bool hide) = 0;
	virtual bool				GetIgnoreGlobalHudDisable(void) = 0;

	// Return true if this HUD element expects an entry in  HudLayout.res
	virtual bool				WantsHudLayoutEntry(void) const = 0;

	// memory handling, uses calloc so members are zero'd out on instantiation

	// For now, CHUdElements declare a single priority value. They will only be hidden
	// by panels with a lower priority and will only lock out panels with a lower priority
	virtual int	GetRenderGroupPriority() = 0;

	virtual void OnSplitScreenStateChanged() = 0;
	virtual void Unknown0() = 0;

public:

	// True if this element is visible, and should think
	bool						m_bActive;

	// m_bWantLateUpdate defaults to false. Set this to true if you need to position something based on the
	// position of a player or other moving game actor.
	// When true, your Think and ProcessInput functions will be called after the simulation updates this means
	// that the Flash VM will not have a chance to run until after the frame has been rendered. This is
	//probably not a big deal, but is good to know.
	bool                        m_bWantLateUpdate;

protected:
	int							m_iHiddenBits;
	int							m_nSplitScreenPlayerSlot;
	bool						m_ignoreGlobalHudDisable;

private:
	const char* m_pElementName;
	bool						m_bNeedsRemove;
	bool						m_bIsParentedToClientDLLRootPanel;

	UtlVector< int >			m_HudRenderGroups;
	Hud* m_pHud;
};

class HudChat
{
public:
	enum ChatFilters : int
	{
		NONE = 0,
		JOINLEAVE = 0x000001,
		NAMECHANGE = 0x000002,
		PUBLICCHAT = 0x000004,
		SERVERMSG = 0x000008,
		TEAMCHANGE = 0x000010,
		ACHIEVEMENT = 0x000020
	};

	void ChatPrintf(int index, int filter, const char* format, ...)
	{
		using Fn = void(__cdecl*)(void*, int, int, const char*, ...);
		return (*(Fn**)this)[27](this, index, filter, format);
	}
};
