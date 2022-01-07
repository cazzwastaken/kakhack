#pragma once
#include <deque>

#include "../sdk/interfaces/gameeventmanager.h"

class EventListener : public GameEventListener2
{
public:
	void Setup(const std::deque<const char*>& events);
	void Destroy();

	virtual void FireGameEvent(GameEvent* event) override;
	virtual int GetEventDebugID() override
	{
		return EVENT_DEBUG_ID_INIT;
	}
};
