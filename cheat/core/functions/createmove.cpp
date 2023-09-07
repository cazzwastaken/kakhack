#include "../hooks.h"
#include "../../../external/x86retspoof/x86RetSpoof.h"

bool __stdcall h::CreateMove(float frameTime, UserCmd* cmd)
{
	static const auto sequence = reinterpret_cast<std::uintptr_t>(m::Scan("client.dll", "FF 23"));
	const auto result = x86RetSpoof::invokeStdcall<bool>((uintptr_t)h::CreateMoveOriginal, sequence, frameTime, cmd);

	if (!cmd || !cmd->commandNumber)
		return result;

	if (result)
		i::engine->SetViewAngles(cmd->viewPoint);

	f::misc.RevealRanks(cmd);
	f::misc.BunnyHop(cmd);
	f::misc.RevealRadar();

	return false;
}