#pragma once
#include "../definitions.h"

#include "netchannel.h"
#include "spatialquery.h"
#include "steamapi.h"

struct PlayerInfo
{
	uint64_t version = 0ULL;
	union
	{
		uint64_t xuid;
		struct
		{
			uint32_t xuidLow;
			uint32_t xuidHigh;
		};
	};

	char name[128];
	int userId;
	char steamId[33];
	uint32_t friendsId;
	char friendsName[128];
	bool fakePlayer;
	bool isHLTV;
	int customFiles[4];
	uint8_t filesDownloaded;
};

class EngineClient
{
public:
	void GetScreenSize(int& width, int& height)
	{
		m::Call<void, int&, int&>(this, 5, width, height);
	}

	bool GetPlayerInfo(int index, PlayerInfo* info)
	{
		return m::Call<bool>(this, 8, index, info);
	}

	int GetPlayerForUserID(int userId)
	{
		return m::Call<int>(this, 9, userId);
	}

	bool IsConsoleVisible()
	{
		return m::Call<bool>(this, 11);
	}

	int GetLocalPlayer()
	{
		return m::Call<int>(this, 12);
	}

	void GetViewAngles(Vector& view)
	{
		m::Call<void, Vector&>(this, 18, view);
	}

	void SetViewAngles(Vector& view)
	{
		m::Call<void, Vector&>(this, 19, view);
	}

	int GetMaxClients()
	{
		return m::Call<int>(this, 20);
	}

	bool IsInGame()
	{
		return m::Call<bool>(this, 26);
	}

	bool IsDrawingLoadingImage()
	{
		return m::Call<bool>(this, 28);
	}

	SpatialQuery* GetBSPTreeQuery()
	{
		return m::Call<SpatialQuery*>(this, 43);
	}

	const char* GetLevelName()
	{
		return m::Call<const char*>(this, 52);
	}

	const char* GetLevelNameShort()
	{
		return m::Call<const char*>(this, 53);
	}

	NetChannelInfo* GetNetChannelInfo()
	{
		return m::Call<NetChannelInfo*>(this, 78);
	}

	bool IsPlayingDemo()
	{
		return m::Call<bool>(this, 82);
	}

	bool IsTakingScreenshot()
	{
		return m::Call<bool>(this, 92);
	}

	bool IsHLTV()
	{
		return m::Call<bool>(this, 93);
	}

	unsigned int GetEngineBuildNumber()
	{
		return m::Call<unsigned int>(this, 104);
	}

	const char* GetProductVersionString()
	{
		return m::Call<const char*>(this, 105);
	}

	void ExecuteClientCmd(const char* command)
	{
		m::Call<void>(this, 108, command);
	}

	void ClientCmdUnrestricted(const char* command, bool fromConsoleOrKeybind = false)
	{
		m::Call<void>(this, 114, command, fromConsoleOrKeybind);
	}

	SteamAPIContext* GetSteamAPIContext()
	{
		return m::Call<SteamAPIContext*>(this, 185);
	}

	bool IsVoiceRecording()
	{
		return m::Call<bool>(this, 224);
	}
};
