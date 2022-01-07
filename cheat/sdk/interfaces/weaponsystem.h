#pragma once
#include <cstddef>

enum WeaponType : int
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL = 1,
	WEAPONTYPE_SUBMACHINEGUN = 2,
	WEAPONTYPE_RIFLE = 3,
	WEAPONTYPE_SHOTGUN = 4,
	WEAPONTYPE_SNIPER = 5,
	WEAPONTYPE_MACHINEGUN = 6,
	WEAPONTYPE_C4 = 7,
	WEAPONTYPE_PLACEHOLDER = 8,
	WEAPONTYPE_GRENADE = 9,
	WEAPONTYPE_HEALTHSHOT = 11,
	WEAPONTYPE_FISTS = 12,
	WEAPONTYPE_BREACHCHARGE = 13,
	WEAPONTYPE_BUMPMINE = 14,
	WEAPONTYPE_TABLET = 15,
	WEAPONTYPE_MELEE = 16
};

class WeaponData
{
public:
	std::byte	pad0[0x14];				// 0x0000
	int			maxClip1;				// 0x0014
	int			maxClip2;				// 0x0018
	int			defaultClip1;			// 0x001C
	int			defaultClip2;			// 0x0020
	int			primaryMaxReserveAmmo; // 0x0024
	int			secondaryMaxReserveAmmo; // 0x0028
	char* worldModel;			// 0x002C
	char* viewModel;			// 0x0030
	char* droppedModel;			// 0x0034
	std::byte	pad1[0x50];				// 0x0038
	char* hudName;				// 0x0088
	char* weaponName;			// 0x008C
	std::byte	pad2[0x2];				// 0x0090
	bool		isMeleeWeapon;			// 0x0092
	std::byte	pad3[0x9];				// 0x0093
	float		weaponWeight;			// 0x009C
	std::byte	pad4[0x28];				// 0x00A0
	int			weaponType;			// 0x00C8
	std::byte	pad5[0x4];				// 0x00CC
	int			weaponPrice;			// 0x00D0
	int			killAward;				// 0x00D4
	std::byte	pad6[0x4];				// 0x00D8
	float		cycleTime;			// 0x00DC
	float		cycleTimeAlt;			// 0x00E0
	std::byte	pad7[0x8];				// 0x00E4
	bool		fullAuto;				// 0x00EC
	std::byte	pad8[0x3];				// 0x00ED
	int			damage;				// 0x00F0
	float		armorRatio;			// 0x00F4
	int			bullets;				// 0x00F8
	float		penetration;			// 0x00FC
	std::byte	pad9[0x8];				// 0x0100
	float		range;				// 0x0108
	float		rangeModifier;		// 0x010C
	float		throwVelocity;		// 0x0110
	std::byte	pad10[0xC];				// 0x0114
	bool		hasSilencer;			// 0x0120
	std::byte	pad11[0xB];				// 0x0121
	char* bulletType;			// 0x012C
	float		maxSpeed;				// 0x0130
	float		maxSpeedAlt;			// 0x0134
	float		spread;				// 0x0138
	float		spreadAlt;			// 0x013C
	std::byte	pad12[0x44];			// 0x0180
	int			recoilSeed;			// 0x0184
	std::byte	pad13[0x20];			// 0x0188
};

class WeaponSystem
{
public:
	virtual void unused1() = 0;
	virtual void unused2() = 0;
	virtual const WeaponData* GetWeaponData(short itemDefinitionIndex) = 0;
};
