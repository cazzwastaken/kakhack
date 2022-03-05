#include "entities.h"

#include "../core/interfaces.h"

void EntityListener::Setup() noexcept
{
	// Reserve 64 slots in playerlist
	playerList.reserve(64);

	i::entity->AddEntityListener(this);
}

void EntityListener::Destroy() noexcept
{
	i::entity->RemoveEntityListener(this);
}

void EntityListener::ClassCheck(BaseEntity* entity, const ClassIndex id) noexcept
{
	switch (id)
	{
	case ClassIndex::CCSPlayer:
	{
		const auto player = static_cast<CSPlayer*>(entity);

		if (entity->Index() == i::engine->GetLocalPlayer())
			g::localPlayer = player;

		playerList.emplace_back(player);
	}
	break;

	case ClassIndex::CCSPlayerResource:
		g::resource = static_cast<CSPlayerResource*>(entity);
		break;

	default:
		break;
	}
}

void EntityListener::Update()  noexcept
{
	for (auto i = 0; i <= i::entity->GetHighestEntityIndex(); ++i)
	{
		const auto entity = i::entity->Get(i);

		if (!entity)
			continue;

		const auto clientClass = entity->GetClientClass();

		if (!clientClass)
			continue;

		ClassCheck(entity, clientClass->classID);
	}
}

void EntityListener::OnEntityCreated(BaseEntity* entity)
{
	if (!entity)
		return;

	const auto clientClass = entity->GetClientClass();

	if (!clientClass)
		return;

	ClassCheck(entity, clientClass->classID);
}

void EntityListener::OnEntityDeleted(BaseEntity* entity)
{
	if (!entity)
		return;

	const auto ent = std::ranges::find(playerList, entity);

	if (ent == playerList.end())
		return;

	playerList.erase(ent);
}
