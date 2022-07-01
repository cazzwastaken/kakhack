#include "../hooks.h"

int __fastcall h::SendDatagram(NetChannel* thisptr, int edx, bf_write* datagram) 
{
	if (i::engine->IsInGame() || !g::localPlayer || datagram != nullptr)
		return SendDatagramOriginal(thisptr, edx, datagram);

	int inReliableState = thisptr->inReliableState;
	int inSequenceNr = thisptr->inSequenceNr;

	/*add latency*/

	thisptr->inReliableState = inReliableState;
	thisptr->inSequenceNr = inSequenceNr;

	return SendDatagramOriginal(thisptr, edx, datagram);
}