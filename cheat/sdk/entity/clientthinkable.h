#pragma once

class ClientUnknown;
class ClientThinkable
{
public:
	virtual ClientUnknown* GetClientUnknown() = 0;

	virtual void ClientThink() = 0;

	virtual void* GetThinkHandle() = 0;
	virtual void SetThinkHandle(int think) = 0;

	virtual void Release() = 0;
};
