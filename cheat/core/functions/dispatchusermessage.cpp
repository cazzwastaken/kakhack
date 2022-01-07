#include "../hooks.h"

bool __stdcall h::DispatchUserMessage(int type, uint32_t flags, int size, const void* message)
{
	if (!v::misc.votes)
		return DispatchUserMessageOriginal(i::client, type, flags, size, message);

	switch (type)
	{
	case CS_UM_VoteStart:
	{
		i::hudChat->ChatPrintf(0, 0, " \x03[kh]\x01 Vote started\n");
		break;
	}
	case CS_UM_VotePass:
		i::hudChat->ChatPrintf(0, 0, " \x03[kh]\x01 Vote \x04Passed\x01\n");
		break;

	case CS_UM_VoteFailed:
		i::hudChat->ChatPrintf(0, 0, " \x03[kh]\x01 \x02Vote\x02 Failed\x01\n");
		break;
	}

	return DispatchUserMessageOriginal(i::client, type, flags, size, message);
}
