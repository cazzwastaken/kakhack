#pragma once
#include "../definitions.h"

#include <stdint.h>
#include <float.h>

enum ClientAlphaDistanceFadeMode
{
	CLIENT_ALPHA_DISTANCE_FADE_USE_CENTER = 0,
	CLIENT_ALPHA_DISTANCE_FADE_USE_NEAREST_BBOX,
	CLIENT_ALPHA_DISTANCE_FADE_MODE_COUNT,
};

enum RenderFx
{
	kRenderFxNone = 0,
	kRenderFxPulseSlow,
	kRenderFxPulseFast,
	kRenderFxPulseSlowWide,
	kRenderFxPulseFastWide,

	kRenderFxFadeSlow,
	kRenderFxFadeFast,
	kRenderFxSolidSlow,
	kRenderFxSolidFast,
	kRenderFxStrobeSlow,

	kRenderFxStrobeFast,
	kRenderFxStrobeFaster,
	kRenderFxFlickerSlow,
	kRenderFxFlickerFast,
	kRenderFxNoDissipation,

	kRenderFxFadeOut,
	kRenderFxFadeIn,
	kRenderFxPulseFastWider,
	kRenderFxGlowShell,

	kRenderFxMax
};

enum RenderMode
{
	kRenderNormal = 0,		// src
	kRenderTransColor,		// c*a+dest*(1-a)
	kRenderTransTexture,	// src*a+dest*(1-a)
	kRenderGlow,			// src*a+dest -- No Z buffer checks -- Fixed size in screen space
	kRenderTransAlpha,		// src*srca+dest*(1-srca)
	kRenderTransAdd,		// src*a+dest
	kRenderEnvironmental,	// not drawn, used for environmental effects
	kRenderTransAddFrameBlend, // use a fractional frame value to blend between animation frames
	kRenderTransAlphaAdd,	// src + dest*(1-a)
	kRenderWorldGlow,		// Same as kRenderGlow but not fixed size in screen space
	kRenderNone,			// Don't render.

	kRenderModeCount,		// must be last
};

class ClientAlphaProperty
{
public:
	virtual ClientUnknown* GetIClientUnknown() = 0;
	virtual void SetAlphaModulation(uint8_t alpha) = 0;
	virtual void SetRenderFX(RenderFx renderFx, RenderMode renderMode, float startTime = FLT_MAX, float duration = 0.0f) = 0;
	virtual void SetFade(float globalFadeScale, float distFadeStart, float distFadeEnd) = 0;
	virtual void SetDesyncOffset(int offset) = 0;
	virtual void EnableAlphaModulationOverride(bool enable) = 0;
	virtual void EnableShadowAlphaModulationOverride(bool enable) = 0;
	virtual void SetDistanceFadeMode(ClientAlphaDistanceFadeMode fadeMode) = 0;
};
