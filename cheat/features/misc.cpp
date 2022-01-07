#include "misc.h"

void Misc::RevealRanks(UserCmd* cmd)
{
	if (!v::misc.ranks)
		return;

	if (cmd->buttons & UserCmd::CommandButtons::IN_SCORE)
		i::client->DispatchUserMessage(CS_UM_ServerRankRevealAll, 0, 0, nullptr);
}

void Misc::RevealRadar()
{
	if (!v::misc.radar)
		return;

	for (const auto player : g::entities.playerList)
	{
		if (!player)
			continue;

		if (player->IsDormant() || !player->IsAlive())
			continue;

		if (player->GetTeam() == g::localPlayer->GetTeam())
			continue;

		player->Spotted() = true;
	}
}

void Misc::RevealVotes(GameEvent* event)
{
	if (!v::misc.votes)
		return;

	if (!g::localPlayer)
		return;

	const auto player = i::entity->Get<CSPlayer>(event->GetInt("entityid"));

	if (!player)
		return;

	auto info = PlayerInfo{ };
	if (!i::engine->GetPlayerInfo(player->Index(), &info))
		return;

	const auto option = event->GetInt("vote_option");

	if (!i::hudChat)
		return;

	i::hudChat->ChatPrintf(0, 0,
		" \x03[kh]\x01 %s voted \x10->\x01 [%s]\n",
		info.name, option ? "\x02No\x01" : "\x04Yes\x01");
}

void Misc::BunnyHop(UserCmd* cmd)
{
	if (!v::misc.bunnyHop)
		return;

	if (!(g::localPlayer->Flags() & 1))
		cmd->buttons &= ~UserCmd::CommandButtons::IN_JUMP;
}

void Misc::SniperCrosshair()
{
	if (!v::misc.sniperCrosshair.first)
		return;

	if (!g::localPlayer)
		return;

	if (!g::localPlayer->IsAlive())
		return;

	const auto weapon = g::localPlayer->GetActiveWeapon();

	if (!weapon)
		return;

	const auto data = i::weapon->GetWeaponData(weapon->ItemDefinitionIndex());

	if (!data)
		return;

	if (data->weaponType != WeaponType::WEAPONTYPE_SNIPER)
		return;

	if (g::localPlayer->IsScoped())
		return;

	int x = g::screen.x / 2;
	int y = g::screen.y / 2;

	i::surface->DrawSetColor({ v::misc.sniperCrosshair.second });
	i::surface->DrawFilledRect(x - 1, y - 3, x + 1, y + 3);
	i::surface->DrawFilledRect(x - 3, y - 1, x + 3, y + 1);
}

void Misc::HitEffect(GameEvent* event)
{
	if (!v::misc.hitEffect.first)
		return;

	if (!g::localPlayer)
		return;

	const auto attackerIndex = i::engine->GetPlayerForUserID(event->GetInt("attacker"));
	const auto attacker = i::entity->Get<CSPlayer>(attackerIndex);

	if (attacker != g::localPlayer)
		return;

	const auto index = i::engine->GetPlayerForUserID(event->GetInt("userid"));
	const auto player = i::entity->Get<CSPlayer>(index);

	if (!player)
		return;

	if (player->GetTeam() == g::localPlayer->GetTeam())
		return;

	constexpr auto mat = "sprites/physbeam.vmt";

	auto info = BeamInfo{ };

	info.modelIndex = i::modelInfo->GetModelIndex(mat);
	info.modelName = mat;

	info.haloIndex = info.modelIndex;
	info.haloName = mat;
	info.haloScale = 2.f;

	info.type = TE_BEAMRINGPOINT;
	info.life = 0.4f;

	info.width = 5.f;
	info.endWidth = 3.f;

	info.fadeLength = 1.f;
	info.amplitude = 1.f;
	info.speed = 0.2f;

	info.startFrame = 0;
	info.frameRate = 30.f;

	info.renderable = true;
	info.segments = 15;
	info.flags = 0;

	info.center = player->GetAbsOrigin() + Vector{ 0.f, 0.f, 5.f };
	info.startRadius = 0.f;
	info.endRadius = 300.f;

	info.SetColor(v::misc.hitEffect.second);

	const auto beam = i::beams->CreateBeamRingPoint(info);

	if (beam)
		i::beams->DrawBeam(beam);
}
