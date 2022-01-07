#pragma once
#include "clientrenderable.h"
#include "clientnetworkable.h"
#include "clientthinkable.h"
#include "clientunknown.h"

#include "../classes/soundinfo.h"

class MouthInfo;
class ClientEntity : public ClientUnknown, public ClientRenderable, public ClientNetworkable, public ClientThinkable
{
public:
	virtual void Release(void) = 0;

	virtual const Vector& GetAbsOrigin(void) const = 0;
	virtual const Vector& GetAbsAngles(void) const = 0;

	virtual MouthInfo* GetMouth(void) = 0;

	virtual bool GetSoundSpatialization(SpatializationInfo& info) = 0;

	virtual bool IsBlurred(void) = 0;

	void SetAbsOrigin(Vector origin)
	{
		using Fn = void(__thiscall*)(void*, const Vector&);
		static auto SetAbsOriginFn = reinterpret_cast<Fn>(m::sigs.setAbsOrigin);
		SetAbsOriginFn(this, origin);
	}

	void SetAbsAngles(Vector view)
	{
		using Fn = void(__thiscall*)(void*, const Vector&);
		static auto SetAbsAnglesFn = reinterpret_cast<Fn>(m::sigs.setAbsAngles);
		SetAbsAnglesFn(this, view);
	}
};
