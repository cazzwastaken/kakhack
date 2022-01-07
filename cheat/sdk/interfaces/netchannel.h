#pragma once
#include "../definitions.h"

#include <cstddef>

class NetChannelInfo
{
public:
	enum
	{
		GENERIC = 0,	// must be first and is default group
		LOCALPLAYER,	// bytes for local player entity update
		OTHERPLAYERS,	// bytes for other players update
		ENTITIES,		// all other entity bytes
		SOUNDS,			// game sounds
		EVENTS,			// event messages
		TEMPENTS,		// temp entities
		USERMESSAGES,	// user messages
		ENTMESSAGES,	// entity messages
		VOICE,			// voice data
		STRINGTABLE,	// a stringtable update
		MOVE,			// client move cmds
		STRINGCMD,		// string command
		SIGNON,			// various signondata
		PAINTMAP,		// paintmap data
		ENCRYPTED,		// encrypted data
		TOTAL,			// must be last and is not a real group
	};

	virtual const char* GetName() const = 0;			// get channel name
	virtual const char* GetAddress() const = 0;			// get channel IP address as string
	virtual float GetTime() const = 0;			// current net time
	virtual float GetTimeConnected() const = 0;	// get connection time in seconds
	virtual int GetBufferSize() const = 0;		// netchannel packet history size
	virtual int GetDataRate() const = 0;		// send data rate in byte/sec

	virtual bool IsLoopback() const = 0;			// true if loopback channel
	virtual bool IsTimingOut() const = 0;		// true if timing out
	virtual bool IsPlayback() const = 0;			// true if demo playback
	virtual float GetLatency(int flow) const = 0; // current latency (RTT), more accurate but jittering
	virtual float GetAvgLatency(int flow) const = 0; // average packet latency in seconds
	virtual float GetAvgLoss(int flow) const = 0; // avg packet loss[0..1]
	virtual float GetAvgChoke(int flow) const = 0; // avg packet choke[0..1]
	virtual float GetAvgData(int flow) const = 0; // data flow in bytes/sec
	virtual float GetAvgPackets(int flow) const = 0; // avg packets/sec
	virtual int GetTotalData(int flow) const = 0; // total flow in/out in bytes
	virtual int GetTotalPackets(int flow) const = 0;
	virtual int GetSequenceNr(int flow) const = 0; // last send seq number
	virtual bool IsValidPacket(int flow, int frame) const = 0; // true if packet was not lost/dropped/chocked/flushed
	virtual float GetPacketTime(int flow, int frame) const = 0; // time when packet was send
	virtual int GetPacketBytes(int flow, int frame, int group) const = 0; // group size of this packet
	virtual bool GetStreamProgress(int flow, int* received, int* total) const = 0; // TCP progress if transmitting
	virtual float GetTimeSinceLastReceived() const = 0; // get time since last received packet in seconds
	virtual	float GetCommandInterpolationAmount(int flow, int frame) const = 0;
	virtual void GetPacketResponseLatency(int flow, int frameNumber, int* latencyMsecs, int* choke) const = 0;
	virtual void GetRemoteFramerate(float* frameTime, float* frameTimeStdDeviation, float* frameStartTimeStdDeviation) const = 0;
	virtual float GetTimeoutSeconds() const = 0;
};

class NetChannel
{
public:
	std::byte	pad0[0x14];				//0x0000
	bool processingMessages;	//0x0014
	bool shouldDelete;			//0x0015
	bool stopProcessing;		//0x0016
	std::byte	pad1[0x1];				//0x0017
	int outSequenceNr;			//0x0018 last send outgoing sequence number
	int inSequenceNr;			//0x001C last received incoming sequence number
	int outSequenceNrAck;		//0x0020 last received acknowledge outgoing sequence number
	int outReliableState;		//0x0024 state of outgoing reliable data (0/1) flip flop used for loss detection
	int inReliableState;		//0x0028 state of incoming reliable data
	int chokedPackets;			//0x002C number of choked packets
	std::byte	pad2[0x414];			//0x0030

	int	SendDatagram(bf_write* datagram)
	{
		return m::Call<int>(this, 46, datagram);
	}

	bool Transmit(bool onlyReliable = false)
	{
		return m::Call<bool>(this, 49, onlyReliable);
	}
};

class NetMessage
{
public:
	virtual ~NetMessage() { }
	virtual void SetNetChannel(void* netChannel) = 0;
	virtual void SetReliable(bool state) = 0;
	virtual bool Process() = 0;
	virtual	bool ReadFromBuffer(bf_read& buffer) = 0;
	virtual	bool WriteToBuffer(bf_write& buffer) = 0;
	virtual bool IsReliable() const = 0;
	virtual int GetType() const = 0;
	virtual int GetGroup() const = 0;
	virtual const char* GetName() const = 0;
	virtual NetChannel* GetNetChannel() const = 0;
	virtual const char* ToString() const = 0;
	virtual size_t		GetSize() const = 0;
};
