#include "skins.h"

void Skins::Run()
{
	if (!g::localPlayer)
		return;

	for (const auto& handle : g::localPlayer->Weapons())
	{
		const auto weapon = i::entity->FromHandle<BaseAttributableItem>(handle);

		if (!weapon)
			continue;

		const auto viewModel = i::entity->FromHandle<BaseViewModel>(g::localPlayer->ViewModel());

		if (!viewModel)
			continue;

		const auto viewModelWeapon = i::entity->FromHandle<BaseAttributableItem>(viewModel->Weapon());

		if (!viewModelWeapon)
			continue;

		const auto worldModel = i::entity->FromHandle<BaseWeaponWorldModel>(weapon->WeaponWorldModel());

		if (!worldModel)
			continue;

		const auto networkable = weapon->GetClientNetworkable();

		if (!networkable)
			continue;

		const auto clientClass = networkable->GetClientClass();

		if (!clientClass)
			continue;

		if (clientClass->classID == ClassIndex::CKnife)
		{
			const auto modelName = GetKnifeModel(WEAPON_KNIFE_KARAMBIT);

			if (!modelName)
				continue;

			const auto index = i::modelInfo->GetModelIndex(modelName);

			// Knife Model Stuff
			if (viewModelWeapon == weapon)
				viewModel->SetModelIndex(index);

			weapon->SetModelIndex(index);
			worldModel->SetModelIndex(index + 1);

			weapon->ItemDefinitionIndex() = WEAPON_KNIFE_KARAMBIT;

			// Attributable item stuff
			weapon->ItemIDHigh() = -1;
			weapon->EntityQuality() = 3;
			weapon->FallbackWear() = 0.0001f;
			weapon->FallbackPaintKit() = 417;
		}
	}
}

void Skins::RemapSequence(RecvProxyData* data, BaseViewModel* viewModel)
{
	const auto owner = i::entity->FromHandle<CSPlayer>(viewModel->Owner());

	if (owner != g::localPlayer)
		return;

	const auto weapon = i::entity->FromHandle<BaseAttributableItem>(viewModel->Weapon());

	if (!weapon)
		return;

	const auto modelName = GetKnifeModel(weapon->ItemDefinitionIndex());

	if (!modelName)
		return;

	auto& sequence = data->value.Int;
	sequence = GetNewSequence(fnv::Hash(modelName), sequence);
}

int Skins::RandomSequence(const int low, const int high)
{
	return rand() % (high - low + 1) + low;
}

int Skins::GetNewSequence(const uint32_t hash, const int sequence)
{
	enum Sequence
	{
		SEQUENCE_DEFAULT_DRAW = 0,
		SEQUENCE_DEFAULT_IDLE1 = 1,
		SEQUENCE_DEFAULT_IDLE2 = 2,
		SEQUENCE_DEFAULT_LIGHT_MISS1 = 3,
		SEQUENCE_DEFAULT_LIGHT_MISS2 = 4,
		SEQUENCE_DEFAULT_HEAVY_MISS1 = 9,
		SEQUENCE_DEFAULT_HEAVY_HIT1 = 10,
		SEQUENCE_DEFAULT_HEAVY_BACKSTAB = 11,
		SEQUENCE_DEFAULT_LOOKAT01 = 12,

		SEQUENCE_BUTTERFLY_DRAW = 0,
		SEQUENCE_BUTTERFLY_DRAW2 = 1,
		SEQUENCE_BUTTERFLY_LOOKAT01 = 13,
		SEQUENCE_BUTTERFLY_LOOKAT03 = 15,

		SEQUENCE_FALCHION_IDLE1 = 1,
		SEQUENCE_FALCHION_HEAVY_MISS1 = 8,
		SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP = 9,
		SEQUENCE_FALCHION_LOOKAT01 = 12,
		SEQUENCE_FALCHION_LOOKAT02 = 13,

		SEQUENCE_CSS_LOOKAT01 = 12,
		SEQUENCE_CSS_LOOKAT02 = 15,

		SEQUENCE_DAGGERS_IDLE1 = 1,
		SEQUENCE_DAGGERS_LIGHT_MISS1 = 2,
		SEQUENCE_DAGGERS_LIGHT_MISS5 = 6,
		SEQUENCE_DAGGERS_HEAVY_MISS2 = 11,
		SEQUENCE_DAGGERS_HEAVY_MISS1 = 12,

		SEQUENCE_BOWIE_IDLE1 = 1,
	};

	switch (hash)
	{
		case fnv::HashConst("models/weapons/v_knife_butterfly.mdl"):
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_DRAW:
			return RandomSequence(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
		case SEQUENCE_DEFAULT_LOOKAT01:
			return RandomSequence(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03);
		default:
			return sequence + 1;
		}
	}
	case fnv::HashConst("models/weapons/v_knife_falchion_advanced.mdl"):
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_IDLE2:
			return SEQUENCE_FALCHION_IDLE1;
		case SEQUENCE_DEFAULT_HEAVY_MISS1:
			return RandomSequence(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP);
		case SEQUENCE_DEFAULT_LOOKAT01:
			return RandomSequence(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02);
		case SEQUENCE_DEFAULT_DRAW:
		case SEQUENCE_DEFAULT_IDLE1:
			return sequence;
		default:
			return sequence - 1;
		}
	}
	case fnv::HashConst("models/weapons/v_knife_css.mdl"):
	{
		const int sequences[] = { SEQUENCE_CSS_LOOKAT01, SEQUENCE_CSS_LOOKAT02 };
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_LOOKAT01:
			return sequences[RandomSequence(0, 1)];
		default:
			return sequence;
		}
	}
	case fnv::HashConst("models/weapons/v_knife_push.mdl"):
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_IDLE2:
			return SEQUENCE_DAGGERS_IDLE1;
		case SEQUENCE_DEFAULT_LIGHT_MISS1:
		case SEQUENCE_DEFAULT_LIGHT_MISS2:
			return RandomSequence(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5);
		case SEQUENCE_DEFAULT_HEAVY_MISS1:
			return RandomSequence(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1);
		case SEQUENCE_DEFAULT_HEAVY_HIT1:
		case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
		case SEQUENCE_DEFAULT_LOOKAT01:
			return sequence + 3;
		case SEQUENCE_DEFAULT_DRAW:
		case SEQUENCE_DEFAULT_IDLE1:
			return sequence;
		default:
			return sequence + 2;
		}
	}
	case fnv::HashConst("models/weapons/v_knife_survival_bowie.mdl"):
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_DRAW:
		case SEQUENCE_DEFAULT_IDLE1:
			return sequence;
		case SEQUENCE_DEFAULT_IDLE2:
			return SEQUENCE_BOWIE_IDLE1;
		default:
			return sequence - 1;
		}
	}
	case fnv::HashConst("models/weapons/v_knife_ursus.mdl"):
	case fnv::HashConst("models/weapons/v_knife_cord.mdl"):
	case fnv::HashConst("models/weapons/v_knife_canis.mdl"):
	case fnv::HashConst("models/weapons/v_knife_outdoor.mdl"):
	case fnv::HashConst("models/weapons/v_knife_skeleton.mdl"):
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_DRAW:
			return RandomSequence(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2);
		case SEQUENCE_DEFAULT_LOOKAT01:
			return RandomSequence(SEQUENCE_BUTTERFLY_LOOKAT01, 14);
		default:
			return sequence + 1;
		}
	}
	case fnv::HashConst("models/weapons/v_knife_stiletto.mdl"):
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_LOOKAT01:
			return RandomSequence(12, 13);
		default:
			return sequence;
		}
	}
	case fnv::HashConst("models/weapons/v_knife_widowmaker.mdl"):
	{
		switch (sequence)
		{
		case SEQUENCE_DEFAULT_LOOKAT01:
			return RandomSequence(14, 15);
		default:
			return sequence;
		}
	}
	default:
		return sequence;
	}
}

const char* Skins::GetKnifeModel(short itemDefinitionIndex)
{
	const auto item = knifeInfo.find(itemDefinitionIndex);
	return item == end(knifeInfo) ? nullptr : item->second;
}
