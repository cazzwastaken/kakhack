#include "../hooks.h"

bool __stdcall h::CreateMove(float frameTime, UserCmd* cmd)
{
	const auto result = CreateMoveOriginal(i::clientMode, frameTime, cmd);

	if (!cmd->commandNumber)
		return result;

	if (result)
		i::engine->SetViewAngles(cmd->viewPoint);

	f::misc.RevealRanks(cmd);
	f::misc.BunnyHop(cmd);
	f::misc.RevealRadar();

	return false;
}