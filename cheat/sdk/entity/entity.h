#pragma once
#include "cliententity.h"

#include "../../core/netvar.h"
#include <array>

class BaseAttributableItem;
class CSPlayer;

class BaseEntity : public ClientEntity
{
public:
	NETVAR(Spotted, "CBaseEntity->m_bSpotted", bool)
	NETVAR(OwnerEntity, "CBaseEntity->m_hOwnerEntity", BaseHandle)
	NETVAR(ModelIndex, "CBaseEntity->m_nModelIndex", unsigned)
	NETVAR(SimulationTime, "CBaseEntity->m_flSimulationTime", float)

	const char* GetClassName()
	{
		return m::Call<const char*>(this, 59);
	}

	void SetModelIndex(const int index)
	{
		m::Call<void>(this, 75, index);
	}

	int GetTeam()
	{
		return m::Call<int>(this, 88);
	}

	int GetHealth()
	{
		return m::Call<int>(this, 122);
	}

	bool IsAlive()
	{
		return m::Call<bool>(this, 156);
	}

	bool IsPlayer()
	{
		return m::Call<bool>(this, 158);
	}

	bool IsWeapon()
	{
		return m::Call<bool>(this, 166);
	}

	void SetSequence(int sequence)
	{
		m::Call<void>(this, 218, sequence);
	}

	BaseAttributableItem* GetActiveWeapon()
	{
		return m::Call<BaseAttributableItem*>(this, 268);
	}

	Vector GetEyePosition()
	{
		Vector v;
		m::Call<void>(this, 285, std::cref(v));
		return v;
	}

	CSPlayer* GetObserverTarget()
	{
		return m::Call<CSPlayer*>(this, 294);
	}

	Vector GetAimPunch()
	{
		Vector v;
		m::Call<void>(this, 346, std::cref(v));
		return v;
	}

	Matrix3x4* GetBoneMatrix();
	Vector GetBonePosition(int bone);
};

class BaseAnimating : public BaseEntity
{
public:

};

class BaseAnimatingOverlay : public BaseAnimating
{
public:
	NETVAR(Sequence, "CBaseAnimating->m_nSequence", unsigned)
};

class BaseFlex : public BaseAnimatingOverlay
{
public:

};

class BaseCombatCharacter : public BaseFlex
{
public:
	NETVAR(Weapons, "CBaseCombatCharacter->m_hMyWeapons", std::array<unsigned long, 48>)
};

class BasePlayer : public BaseCombatCharacter
{
public:
	NETVAR(Flags, "CBasePlayer->m_fFlags", int)
	NETVAR(Velocity, "CBasePlayer->m_vecVelocity[0]", Vector)
	NETVAR(ViewModel, "CBasePlayer->m_hViewModel[0]", BaseHandle)
	NETVAR(TickBase, "CBasePlayer->m_nTickBase", int)
};

class CSPlayer : public BasePlayer
{
public:
	NETVAR(IsScoped, "CCSPlayer->m_bIsScoped", bool)
	NETVAR(IsDefusing, "CCSPlayer->m_bIsDefusing", bool)
	NETVAR(HasGunGameImmunity, "CCSPlayer->m_bGunGameImmunity", bool)
	NETVAR(Account, "CCSPlayer->m_iAccount", int)
	NETVAR(InBombZone, "CCSPlayer->m_bInBombZone", bool)
	NETVAR(HasDefuser, "CCSPlayer->m_bHasDefuser", bool)
	NETVAR(HasHelmet, "CCSPlayer->m_bHasHelmet", bool)
};

class CSPlayerResource : public BaseEntity
{
public:
	NETVAR(PlayerC4, "CCSPlayerResource->m_iPlayerC4", int)
	NETVAR(PlayerVIP, "CCSPlayerResource->m_iPlayerVIP", int)
	NETVAR(BombsiteCenterA, "CCSPlayerResource->m_bombsiteCenterA", Vector)
	NETVAR(BombsiteCenterB, "CCSPlayerResource->m_bombsiteCenterB", Vector)
};

class BaseCombatWeapon : public BaseEntity
{
public:
	NETVAR(ViewModelIndex, "CBaseCombatWeapon->m_iViewModelIndex", int)
	NETVAR(WorldModelIndex, "CBaseCombatWeapon->m_iWorldModelIndex", int)
	NETVAR(WorldDroppedModelIndex, "CBaseCombatWeapon->m_iWorldDroppedModelIndex", int)
	NETVAR(WeaponWorldModel, "CBaseCombatWeapon->m_hWeaponWorldModel", BaseHandle)
};

class BaseAttributableItem : public BaseCombatWeapon
{
public:
	NETVAR(AccountID, "CBaseAttributableItem->m_iAccountID", int)
	NETVAR(ItemDefinitionIndex, "CBaseAttributableItem->m_iItemDefinitionIndex", short)
	NETVAR(ItemIDHigh, "CBaseAttributableItem->m_iItemIDHigh", int)
	NETVAR(EntityQuality, "CBaseAttributableItem->m_iEntityQuality", int)
	NETVAR(CustomName, "CBaseAttributableItem->m_szCustomName", char[32])
	NETVAR(FallbackPaintKit, "CBaseAttributableItem->m_nFallbackPaintKit", unsigned)
	NETVAR(FallbackSeed, "CBaseAttributableItem->m_nFallbackSeed", unsigned)
	NETVAR(FallbackWear, "CBaseAttributableItem->m_flFallbackWear", float)
	NETVAR(FallbackStatTrak, "CBaseAttributableItem->m_nFallbackStatTrak", unsigned)
};

class BaseViewModel : public BaseEntity
{
public:
	NETVAR(Owner, "CBaseViewModel->m_hOwner", BaseHandle)
	NETVAR(Weapon, "CBaseViewModel->m_hWeapon", BaseHandle)
	NETPROP(SequenceProp, "CBaseViewModel->m_nSequence")
};

class BaseWeaponWorldModel : public BaseEntity
{
public:

};
