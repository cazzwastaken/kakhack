#pragma once
#include "../core/interfaces.h"

class Visuals
{
public:
	void Renderables();
	void WorldColor();
	void Glow();
	bool ColoredModel(MatRenderContext* context,
		const DrawModelState& state,
		const ModelRenderInfo& info,
		Matrix3x4* customBoneToWorld);
};
