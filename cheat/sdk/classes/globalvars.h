#pragma once

class GlobalVarsBase
{
public:
	float realTime;
	int frameCount;
	float absFrameTime;
	float absFrameStartTime;
	float currentTime;
	float frameTime;
	int maxClients;
	int tickCount;
	float intervalPerTick;
	float interpolationAmount;
	int frameSimulationTicks;
	int networkProtocol;
	void* saveData;
	bool client;
	bool remoteClient;
	int timestampNetworkingBase;
	int timestampRandomizeWindow;
};
