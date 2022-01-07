#pragma once
#include "appsystem.h"
#include "convar.h"

class Color;
class ConCmd;
class ConBase;
class EngineConVar : public AppSystem
{
public:
	virtual int	AllocateDLLIdentifier() = 0;
	virtual void			RegisterConCommand(ConVar* commandBase, int defaultValue = 1) = 0;
	virtual void			UnregisterConCommand(ConVar* commandBase) = 0;
	virtual void			UnregisterConCommands(int id) = 0;
	virtual const char* GetCommandLineValue(const char* variableName) = 0;
	virtual ConBase* FindCommandBase(const char* name) = 0;
	virtual const ConBase* FindCommandBase(const char* name) const = 0;
	virtual ConVar* FindVar(const char* variableName) = 0;
	virtual const ConVar* FindVar(const char* variableName) const = 0;
	virtual ConCmd* FindCommand(const char* name) = 0;
	virtual const ConCmd* FindCommand(const char* name) const = 0;
	virtual void			InstallGlobalChangeCallback(ChangeCallbackFn callback) = 0;
	virtual void			RemoveGlobalChangeCallback(ChangeCallbackFn callback) = 0;
	virtual void			CallGlobalChangeCallbacks(ConVar* var, const char* oldString, float oldValue) = 0;
	virtual void			InstallConsoleDisplayFunc(void* displayFunc) = 0;
	virtual void			RemoveConsoleDisplayFunc(void* displayFunc) = 0;
	virtual void			ConsoleColorPrintf(const Color& color, const char* format, ...) const = 0;
	virtual void			ConsolePrintf(const char* format, ...) const = 0;
	virtual void			ConsoleDPrintf(const char* format, ...) const = 0;
	virtual void			RevertFlaggedConVars(int flag) = 0;
};
