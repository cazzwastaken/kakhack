#pragma once
#include "../definitions.h"

enum GameType : int
{
	GAMETYPE_UNKNOWN = -1,
	GAMETYPE_CLASSIC,
	GAMETYPE_GUNGAME,
	GAMETYPE_TRAINING,
	GAMETYPE_CUSTOM,
	GAMETYPE_COOPERATIVE,
	GAMETYPE_SKIRMISH,
	GAMETYPE_FREEFORALL
};

enum GameMode : int
{
	GAMEMODE_UNKNOWN = 0,
	GAMEMODE_CASUAL,
	GAMEMODE_COMPETITIVE,
	GAMEMODE_WINGMAN,
	GAMEMODE_ARMSRACE,
	GAMEMODE_DEMOLITION,
	GAMEMODE_DEATHMATCH,
	GAMEMODE_GUARDIAN,
	GAMEMODE_COOPSTRIKE,
	GAMEMODE_DANGERZONE
};

class GameTypes
{
public:
	int GetCurrentGameType()
	{
		return m::Call<int>(this, 8);
	}

	int GetCurrentGameMode()
	{
		return m::Call<int>(this, 9);
	}

	const char* GetCurrentMapName()
	{
		return m::Call<const char*>(this, 10);
	}

	const char* GetCurrentGameTypeNameID()
	{
		return m::Call<const char*>(this, 11);
	}

	const char* GetCurrentGameModeNameID()
	{
		return m::Call<const char*>(this, 13);
	}
};
