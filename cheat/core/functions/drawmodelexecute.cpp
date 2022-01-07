#include "../hooks.h"

void __stdcall h::DrawModelExecute(MatRenderContext* context, const DrawModelState& state, const ModelRenderInfo& info, Matrix3x4* customBoneToWorld)
{
	if (i::studio->IsForcedMaterialOverride())
		return DrawModelExecuteOriginal(i::modelRender, context, state, info, customBoneToWorld);

	f::visuals.ColoredModel(context, state, info, customBoneToWorld) ?
		i::studio->ForcedMaterialOverride(nullptr) :
		DrawModelExecuteOriginal(i::modelRender, context, state, info, customBoneToWorld);
}
