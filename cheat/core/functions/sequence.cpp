#include "../hooks.h"

void __cdecl h::Sequence(const RecvProxyData* data, void* entity, void* output)
{
	if (!g::localPlayer || !g::localPlayer->IsAlive())
		return SequenceOriginal(data, entity, output);

	const auto proxyData = const_cast<RecvProxyData*>(data);
	const auto viewModel = static_cast<BaseViewModel*>(entity);

	f::skins.RemapSequence(proxyData, viewModel);

	SequenceOriginal(data, entity, output);
}
