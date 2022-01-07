#include "../hooks.h"

void __stdcall h::FrameStageNotify(ClientFrameStage stage)
{
	switch (stage)
	{
	case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
		f::skins.Run();
		break;

	case FRAME_RENDER_START:
		{
			if (g::localPlayer)
			{
				f::misc.RevealRadar();
			}
		}
		break;
	}

	FrameStageNotifyOriginal(i::client, stage);
}
