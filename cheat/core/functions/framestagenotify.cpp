#include "../hooks.h"

void __stdcall h::FrameStageNotify(ClientFrameStage stage)
{
	switch (stage)
	{
	case FRAME_NET_UPDATE_POSTDATAUPDATE_START:
		f::skins.Run();
		break;
	}

	FrameStageNotifyOriginal(i::client, stage);
}
