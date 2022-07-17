#include "visuals.h"

#include "../core/hooks.h"
#include <string>

void Visuals::Renderables()
{
	if (!g::localPlayer)
		return;

	for (const auto& player : g::entities.playerList)
	{
		if (!player)
			continue;

		if (player->IsDormant() || !player->IsAlive())
			continue;

		if (player->GetTeam() == g::localPlayer->GetTeam())
			continue;

		if (!g::localPlayer->IsAlive())
		{
			const auto target = g::localPlayer->GetObserverTarget();

			if (target == player)
				continue;
		}

		auto feet = Vector{ };
		if (i::debug->ScreenPosition(player->GetAbsOrigin() - Vector{ 0, 0, 5 }, feet))
			continue;

		const auto matrix = player->GetBoneMatrix();

		if (!matrix)
			continue;

		auto head = Vector{ };
		if (i::debug->ScreenPosition(matrix[8].at(3) + Vector{ 0, 0, 10 }, head))
			continue;

		const auto height = feet.y - head.y;
		const auto width = height * 0.23;
		const auto left = int(feet.x - width);
		const auto right = int(feet.x + width);

		if (v::visuals.box.first)
		{
			g::render.Rect(left, int(head.y), right, int(feet.y), { v::visuals.box.second });

			if (v::visuals.outlined.first)
			{
				// More effecient than using renderer here :)
				// because only one DrawSetColor call
				i::surface->DrawSetColor({ v::visuals.outlined.second });
				i::surface->DrawOutlinedRect(left + 1, int(head.y) + 1, right - 1, int(feet.y) - 1);
				i::surface->DrawOutlinedRect(left - 1, int(head.y) - 1, right + 1, int(feet.y) + 1);
			}
		}

		if (v::visuals.filled.first)
			g::render.RectFilled(left + 1, int(head.y) + 1, right - 1, int(feet.y) - 1, { v::visuals.filled.second });

		if (v::visuals.headdot.first)
		{
			auto realHead = Vector{ };
			i::debug->ScreenPosition(matrix[BONE_HEAD].at(3), realHead);

			g::render.Circle(int(realHead.x), int(realHead.y), 1, 10, { v::visuals.headdot.second });
		}

		if (v::visuals.name.first)
		{
			auto info = PlayerInfo{ };
			if (!i::engine->GetPlayerInfo(player->Index(), &info))
				continue;

			wchar_t name[128];

			if (MultiByteToWideChar(CP_UTF8, 0, info.name, -1, name, 128) < 0)
				continue;

			int w, h;
			i::surface->GetTextSize(g::render.tahoma, name, w, h);

			// If we are drawing boxes, align name to box
			// else align to head (looks better)
			if (v::visuals.box.first || v::visuals.filled.first)
				g::render.Text(name,
					{ v::visuals.name.second },
					int((left + width) - (w / 2.f)),
					int(head.y - 15),
					g::render.tahoma);
			else
				g::render.Text(name,
					{ v::visuals.name.second },
					int(head.x - (w / 2.f)),
					int(head.y - 12),
					g::render.tahoma);
		}
	}
}

void Visuals::WorldColor()
{
	// Color world and sky
	for (auto i = i::materialSystem->FirstMaterial();
		i != i::materialSystem->InvalidMaterial();
		i = i::materialSystem->NextMaterial(i))
	{
		const auto material = i::materialSystem->GetMaterial(i);

		if (!material || material->IsErrorMaterial())
			continue;

		const auto group = std::string_view(material->GetTextureGroupName());

		if (group.starts_with("World"))
			material->Modulate(v::visuals.world.data());
		else if (group.starts_with("Sky"))
			material->Modulate(v::visuals.sky.data());
	}
}

void Visuals::Glow()
{
	if (!g::localPlayer)
		return;

	for (auto i = 0; i < i::glow->glowObjectDefinitions.Count(); ++i)
	{
		auto& glow = i::glow->glowObjectDefinitions[i];

		if (glow.IsUnused())
			continue;

		if (!glow.entity)
			continue;

		const auto clientClass = glow.entity->GetClientClass();

		if (!clientClass)
			continue;

		switch (clientClass->classID)
		{
		case ClassIndex::CCSPlayer:
		{
			if (!v::visuals.player.first)
				break;

			const auto player = static_cast<CSPlayer*>(glow.entity);

			if (player->GetTeam() == g::localPlayer->GetTeam())
				break;

			if (!player->IsAlive())
				break;

			glow.SetColor(v::visuals.player.second.data());
			break;
		}

		case ClassIndex::CChicken:
			if (!v::visuals.chicken.first)
				break;

			glow.SetColor(v::visuals.chicken.second.data());
			break;

		case ClassIndex::CC4:
		case ClassIndex::CPlantedC4:
			if (!v::visuals.bomb.first)
				break;

			glow.SetColor(v::visuals.bomb.second.data());
			break;

		case ClassIndex::CBaseCSGrenadeProjectile:
		case ClassIndex::CBreachChargeProjectile:
		case ClassIndex::CBumpMineProjectile:
		case ClassIndex::CDecoyProjectile:
		case ClassIndex::CMolotovProjectile:
		case ClassIndex::CSensorGrenadeProjectile:
		case ClassIndex::CSmokeGrenadeProjectile:
			if (!v::visuals.grenade.first)
				break;

			glow.SetColor(v::visuals.grenade.second.data());
			break;

		default:
			if (!v::visuals.weapon.first)
				break;

			if (!glow.entity->IsWeapon())
				break;

			glow.SetColor(v::visuals.weapon.second.data());
			break;
		}
	}
}

bool Visuals::ColoredModel(MatRenderContext* context,
	const DrawModelState& state,
	const ModelRenderInfo& info,
	Matrix3x4* customBoneToWorld)
{
	if (!g::localPlayer)
		return false;

	static auto material = i::materialSystem->FindMaterial("debug/debugambientcube");

	if (static auto once = true; once)
	{
		material->IncrementReferenceCount();
		once = !once;
	}

	const auto name = std::string_view(info.model->name);

	if (name.starts_with("models/weapons/v_"))
	{
		if (strstr(name.data() + 17, "sleeve"))
		{
			if (!v::visuals.sleeve.first)
				return false;

			material->Modulate(v::visuals.sleeve.second.data());
			material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
			i::studio->ForcedMaterialOverride(material);
			h::DrawModelExecuteOriginal(i::modelRender, context, state, info, customBoneToWorld);
			return true;
		}
		else if (strstr(name.data() + 17, "arms"))
		{
			if (!v::visuals.arm.first)
				return false;

			material->Modulate(v::visuals.arm.second.data());
			material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
			i::studio->ForcedMaterialOverride(material);
			h::DrawModelExecuteOriginal(i::modelRender, context, state, info, customBoneToWorld);
			return true;
		}
		else if (!strstr(name.data() + 17, "tablet") && !strstr(name.data() + 17, "parachute") && !strstr(name.data() + 17, "fists"))
		{
			if (!v::visuals.item.first)
				return false;

			material->Modulate(v::visuals.item.second.data());
			material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
			i::studio->ForcedMaterialOverride(material);
			h::DrawModelExecuteOriginal(i::modelRender, context, state, info, customBoneToWorld);
			return true;
		}
	}
	else
	{
		const auto player = i::entity->Get<CSPlayer>(info.entityIndex);

		if (!player)
			return false;

		if (!player->IsPlayer())
			return false;

		if (player->GetTeam() == g::localPlayer->GetTeam())
			return false;

		auto applied = false;

		if (v::visuals.hidden.first)
		{
			material->Modulate(v::visuals.hidden.second.data());
			material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
			i::studio->ForcedMaterialOverride(material);
			h::DrawModelExecuteOriginal(i::modelRender, context, state, info, customBoneToWorld);
			applied = true;
		}

		if (v::visuals.visible.first)
		{
			material->Modulate(v::visuals.visible.second.data());
			material->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
			i::studio->ForcedMaterialOverride(material);
			h::DrawModelExecuteOriginal(i::modelRender, context, state, info, customBoneToWorld);
			applied = true;
		}

		return applied;
	}

	return false;
}
