#pragma once
#include "../data/vector.h"

class Effects
{
public:
	//
	// Particle effects
	//
	virtual void Beam(const Vector& Start, const Vector& End, int modelIndex,
		int nHaloIndex, unsigned char frameStart, unsigned char frameRate,
		float flLife, unsigned char width, unsigned char endWidth, unsigned char fadeLength,
		unsigned char noise, unsigned char red, unsigned char green,
		unsigned char blue, unsigned char brightness, unsigned char speed) = 0;

	//-----------------------------------------------------------------------------
	// Purpose: Emits smoke sprites.
	// Input  : origin - Where to emit the sprites.
	//			scale - Sprite scale * 10.
	//			framerate - Framerate at which to animate the smoke sprites.
	//-----------------------------------------------------------------------------
	virtual void Smoke(const Vector& origin, int modelIndex, float scale, float framerate) = 0;

	virtual void Sparks(const Vector& position, int nMagnitude = 1, int nTrailLength = 1, const Vector* dir = NULL) = 0;

	virtual void Dust(const Vector& pos, const Vector& dir, float size, float speed) = 0;

	virtual void MuzzleFlash(const Vector& origin, const Vector& angles, float scale, int iType) = 0;

	// like ricochet, but no sound
	virtual void MetalSparks(const Vector& position, const Vector& direction) = 0;

	virtual void EnergySplash(const Vector& position, const Vector& direction, bool explosive = false) = 0;

	virtual void Ricochet(const Vector& position, const Vector& direction) = 0;

	virtual float Time() = 0;
	virtual bool IsServer() = 0;

	virtual void SuppressEffectsSounds(bool bSuppress) = 0;
};
