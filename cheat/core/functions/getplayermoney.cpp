#include "../hooks.h"

int __fastcall h::GetPlayerMoney(void* thisptr, void* edx, int entityIndex)
{
	if (!v::misc.money)
		return GetPlayerMoneyOriginal(thisptr, entityIndex);

	const auto player = i::entity->Get<CSPlayer>(entityIndex);

	if (!player || !player->IsPlayer())
		return GetPlayerMoneyOriginal(thisptr, entityIndex);

	if (player->GetTeam() == g::localPlayer->GetTeam())
		return GetPlayerMoneyOriginal(thisptr, entityIndex);

	// This figure will be slightly outdated due to dormancy
	return player->Account();
}
