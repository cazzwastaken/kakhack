#pragma once
#include "../definitions.h"

constexpr auto EVENT_DEBUG_ID_INIT = 42;
constexpr auto EVENT_DEBUG_ID_SHUTDOWN = 13;

class GameEvent
{
public:
	virtual					~GameEvent() { }
	virtual const char* GetName() const = 0;

	virtual bool			IsReliable() const = 0;
	virtual bool			IsLocal() const = 0;
	virtual bool			IsEmpty(const char* keyName = nullptr) = 0;

	virtual bool			GetBool(const char* keyName = nullptr, bool defualt = false) = 0;
	virtual int				GetInt(const char* keyName = nullptr, int defualt = 0) = 0;
	virtual uint64_t	GetUint64(const char* keyName = nullptr, uint64_t defualt = 0) = 0;
	virtual float			GetFloat(const char* keyName = nullptr, float defualt = 0.f) = 0;
	virtual const char* GetString(const char* keyName = nullptr, const char* defualt = "") = 0;
	virtual const wchar_t* GetWString(const char* keyName = nullptr, const wchar_t* defualt = L"") = 0;
	virtual const void* GetPtr(const char* keyName = nullptr) const = 0;

	virtual void			SetBool(const char* keyName, bool value) = 0;
	virtual void			SetInt(const char* keyName, int value) = 0;
	virtual void			SetUint64(const char* keyName, uint64_t value) = 0;
	virtual void			SetFloat(const char* keyName, float value) = 0;
	virtual void			SetString(const char* keyName, const char* value) = 0;
	virtual void			SetWString(const char* keyName, const wchar_t* value) = 0;
	virtual void			SetPtr(const char* keyName, const void* value) = 0;

	virtual bool			ForEventData(void* event) const = 0;
};

class GameEventListener2
{
public:
	virtual			~GameEventListener2() { }
	virtual void	FireGameEvent(GameEvent* pEvent) = 0;
	virtual int		GetEventDebugID()
	{
		return debugId;
	}

	int	debugId;
};

class CSVCMsg_GameEvent;
class GameEventManager2
{
public:
	virtual				~GameEventManager2() { }
	virtual int			LoadEventsFromFile(const char* fileName) = 0;
	virtual void		Reset() = 0;
	virtual bool		AddListener(GameEventListener2* listener, const char* name, bool serverSide) = 0;
	virtual bool		FindListener(GameEventListener2* listener, const char* name) = 0;
	virtual void		RemoveListener(GameEventListener2* listener) = 0;
	virtual void		AddListenerGlobal(GameEventListener2* listener, bool serverSide) = 0;
	virtual GameEvent* CreateNewEvent(const char* name, bool force = false, int* unknown = nullptr) = 0;
	virtual bool		FireEvent(GameEvent* event, bool dontBroadcast = false) = 0;
	virtual bool		FireEventClientSide(GameEvent* event) = 0;
	virtual GameEvent* DuplicateEvent(GameEvent* event) = 0;
	virtual void		FreeEvent(GameEvent* event) = 0;
	virtual bool		SerializeEvent(GameEvent* event, CSVCMsg_GameEvent* eventMsg) = 0;
	virtual GameEvent* UnserializeEvent(const CSVCMsg_GameEvent& eventMsg) = 0;
	virtual KeyValues* GetEventDataTypes(GameEvent* event) = 0;
};
