#include "events.h"
#include "../core/interfaces.h"

#include <stdexcept>

#include "../features/features.h"

void EventListener::Setup(const std::deque<const char*>& events)
{
	if (events.empty())
		return;

	for (auto event : events)
	{
		i::events->AddListener(this, event, false);

		if (!i::events->FindListener(this, event))
			throw std::runtime_error("Failed add event listener");
	}
}

void EventListener::Destroy()
{
	i::events->RemoveListener(this);
}

void EventListener::FireGameEvent(GameEvent* event)
{
	if (!event)
		return;

	switch (fnv::Hash(event->GetName()))
	{
	case fnv::HashConst("vote_cast"):
		f::misc.RevealVotes(event);
		break;

	case fnv::HashConst("player_hurt"):
		f::misc.HitEffect(event);
		break;

	default:
		break;
	}
}
