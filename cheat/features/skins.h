#pragma once
#include "../core/interfaces.h"

#include <map>

class Skins
{
public:
	void Run();
	void RemapSequence(RecvProxyData* data, BaseViewModel* viewModel);

private:
	// Knife Related
	int RandomSequence(const int low, const int high);
	int GetNewSequence(const uint32_t hash, const int sequence);
	const char* GetKnifeModel(short itemDefinitionIndex);

	const std::map<int, const char*> knifeInfo
	{
		{WEAPON_KNIFE,"models/weapons/v_knife_default_ct.mdl"},
		{WEAPON_KNIFE_T,"models/weapons/v_knife_default_t.mdl"},
		{WEAPON_KNIFE_BAYONET, "models/weapons/v_knife_bayonet.mdl"},
		{WEAPON_KNIFE_CSS, "models/weapons/v_knife_css.mdl"},
		{WEAPON_KNIFE_FLIP, "models/weapons/v_knife_flip.mdl"},
		{WEAPON_KNIFE_GUT, "models/weapons/v_knife_gut.mdl"},
		{WEAPON_KNIFE_KARAMBIT, "models/weapons/v_knife_karam.mdl"},
		{WEAPON_KNIFE_M9_BAYONET, "models/weapons/v_knife_m9_bay.mdl"},
		{WEAPON_KNIFE_TACTICAL, "models/weapons/v_knife_tactical.mdl"},
		{WEAPON_KNIFE_FALCHION, "models/weapons/v_knife_falchion_advanced.mdl"},
		{WEAPON_KNIFE_SURVIVAL_BOWIE, "models/weapons/v_knife_survival_bowie.mdl"},
		{WEAPON_KNIFE_BUTTERFLY, "models/weapons/v_knife_butterfly.mdl"},
		{WEAPON_KNIFE_PUSH, "models/weapons/v_knife_push.mdl"},
		{WEAPON_KNIFE_CORD, "models/weapons/v_knife_cord.mdl"},
		{WEAPON_KNIFE_CANIS, "models/weapons/v_knife_canis.mdl"},
		{WEAPON_KNIFE_URSUS,"models/weapons/v_knife_ursus.mdl"},
		{WEAPON_KNIFE_GYPSY_JACKKNIFE, "models/weapons/v_knife_gypsy_jackknife.mdl"},
		{WEAPON_KNIFE_OUTDOOR, "models/weapons/v_knife_outdoor.mdl"},
		{WEAPON_KNIFE_STILETTO, "models/weapons/v_knife_stiletto.mdl"},
		{WEAPON_KNIFE_WIDOWMAKER, "models/weapons/v_knife_widowmaker.mdl"},
		{WEAPON_KNIFE_SKELETON, "models/weapons/v_knife_skeleton.mdl"}
	};
};
