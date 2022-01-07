#pragma once
#include "../definitions.h"

#include "../classes/globalvars.h"
#include "../classes/clientclass.h"

enum ClientFrameStage
{
	FRAME_UNDEFINED = -1,
	FRAME_START,

	FRAME_NET_UPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	FRAME_NET_UPDATE_END,

	FRAME_RENDER_START,
	FRAME_RENDER_END,

	FRAME_NET_FULL_FRAME_UPDATE_ON_REMOVE
};

enum UserMessages : int
{
	CS_UM_VGUIMenu = 1,
	CS_UM_Geiger = 2,
	CS_UM_Train = 3,
	CS_UM_HudText = 4,
	CS_UM_SayText = 5,
	CS_UM_SayText2 = 6,
	CS_UM_TextMsg = 7,
	CS_UM_HudMsg = 8,
	CS_UM_ResetHud = 9,
	CS_UM_GameTitle = 10,
	CS_UM_Shake = 12,
	CS_UM_Fade = 13,
	CS_UM_Rumble = 14,
	CS_UM_CloseCaption = 15,
	CS_UM_CloseCaptionDirect = 16,
	CS_UM_SendAudio = 17,
	CS_UM_RawAudio = 18,
	CS_UM_VoiceMask = 19,
	CS_UM_RequestState = 20,
	CS_UM_Damage = 21,
	CS_UM_RadioText = 22,
	CS_UM_HintText = 23,
	CS_UM_KeyHintText = 24,
	CS_UM_ProcessSpottedEntityUpdate = 25,
	CS_UM_ReloadEffect = 26,
	CS_UM_AdjustMoney = 27,
	CS_UM_UpdateTeamMoney = 28,
	CS_UM_StopSpectatorMode = 29,
	CS_UM_KillCam = 30,
	CS_UM_DesiredTimescale = 31,
	CS_UM_CurrentTimescale = 32,
	CS_UM_AchievementEvent = 33,
	CS_UM_MatchEndConditions = 34,
	CS_UM_DisconnectToLobby = 35,
	CS_UM_PlayerStatsUpdate = 36,
	CS_UM_DisplayInventory = 37,
	CS_UM_WarmupHasEnded = 38,
	CS_UM_ClientInfo = 39,
	CS_UM_XRankGet = 40,
	CS_UM_XRankUpd = 41,
	CS_UM_CallVoteFailed = 45,
	CS_UM_VoteStart = 46,
	CS_UM_VotePass = 47,
	CS_UM_VoteFailed = 48,
	CS_UM_VoteSetup = 49,
	CS_UM_ServerRankRevealAll = 50,
	CS_UM_SendLastKillerDamageToClient = 51,
	CS_UM_ServerRankUpdate = 52,
	CS_UM_ItemPickup = 53,
	CS_UM_ShowMenu = 54,
	CS_UM_BarTime = 55,
	CS_UM_AmmoDenied = 56,
	CS_UM_MarkAchievement = 57,
	CS_UM_MatchStatsUpdate = 58,
	CS_UM_ItemDrop = 59,
	CS_UM_GlowPropTurnOff = 60,
	CS_UM_SendPlayerItemDrops = 61,
	CS_UM_RoundBackupFilenames = 62,
	CS_UM_SendPlayerItemFound = 63,
	CS_UM_ReportHit = 64,
	CS_UM_XpUpdate = 65,
	CS_UM_QuestProgress = 66,
	CS_UM_ScoreLeaderboardData = 67,
	CS_UM_PlayerDecalDigitalSignature = 68
};

class EngineSprite;
class ViewSetup;

class BaseClientDll
{
public:
	virtual int Connect(CreateInterfaceFn appSystemFactory, GlobalVarsBase* globals) = 0;
	virtual void Disconnect() = 0;
	virtual int Init(CreateInterfaceFn appSystemFactory, GlobalVarsBase* globals) = 0;

	virtual void PostInit() = 0;
	virtual void Shutdown(void) = 0;

	virtual void LevelInitPreEntity(const char* mapName) = 0;
	virtual void LevelInitPostEntity() = 0;
	virtual void LevelShutdown(void) = 0;

	virtual ClientClass* GetAllClasses(void) = 0;

	virtual int HudVidInit(void) = 0;
	virtual void HudProcessInput(bool active) = 0;
	virtual void HudUpdate(bool active) = 0;
	virtual void HudReset(void) = 0;
	virtual void HudText(const char* message) = 0;

	virtual void Unknown1() = 0;
	virtual void Unknown2() = 0;

	virtual void IN_ActivateMouse(void) = 0;
	virtual void IN_DeactivateMouse(void) = 0;
	virtual void IN_Accumulate(void) = 0;
	virtual void IN_ClearStates(void) = 0;
	virtual bool IN_IsKeyDown(const char* name, bool& isDown) = 0;

	virtual int IN_KeyEvent(int eventcode, ButtonCode keynum, const char* pszCurrentBinding) = 0;

	virtual void CreateMove(int sequence_number, float input_sample_frametime, bool active) = 0;
	virtual void ExtraMouseSample(float frametime, bool active) = 0;
	virtual bool WriteUsercmdDeltaToBuffer(int slot, bf_write* buf, int from, int to, bool isnewcommand) = 0;
	virtual void EncodeUserCmdToBuffer(int nSlot, bf_write& buf, int slot) = 0;
	virtual void DecodeUserCmdFromBuffer(int nSlot, bf_read& buf, int slot) = 0;

	virtual void View_Render(Rect* rect) = 0;
	virtual void RenderView(const ViewSetup& view, int clearFlags, int whatToDraw) = 0;

	virtual void Unknown3() = 0;
	virtual void Unknown4() = 0;

	virtual void InitSprite(EngineSprite* sprite, const char* loadName) = 0;
	virtual void ShutdownSprite(EngineSprite* sprite) = 0;

	virtual int GetSpriteSize(void) const = 0;

	virtual void VoiceStatus(int entityIndex, int slot, bool talking) = 0;

	virtual bool PlayerAudible(int playerIndex) = 0;

	virtual void InstallStringTableCallback(const char* tableName) = 0;

	virtual void FrameStageNotify(ClientFrameStage curStage) = 0;

	virtual bool DispatchUserMessage(int type, uint32_t flags, int size, const void* message) = 0;
};
