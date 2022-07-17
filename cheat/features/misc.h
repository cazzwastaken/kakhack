#pragma once
#include "../core/interfaces.h"

class Misc
{
public:
	void RevealRanks(UserCmd* cmd);
	void RevealRadar();
	void RevealVotes(GameEvent* event);
	void BunnyHop(UserCmd* cmd);
	void SniperCrosshair();
	void HitEffect(GameEvent* event);
};
