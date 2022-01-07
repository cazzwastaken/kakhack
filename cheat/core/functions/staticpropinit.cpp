#include "../hooks.h"

bool __fastcall h::StaticPropInit(StaticProp* thisptr, void* edx, int index, StaticPropLump& lump, Model* model)
{
	// P static prop coloring
	lump.m_DiffuseModulation.r = v::visuals.props[0] * 255.f;
	lump.m_DiffuseModulation.g = v::visuals.props[1] * 255.f;
	lump.m_DiffuseModulation.b = v::visuals.props[2] * 255.f;
	lump.m_DiffuseModulation.a = v::visuals.props[3] * 255.f;

	return StaticPropInitOriginal(thisptr, index, lump, model);
}
