#pragma once
#include "material.h"
#include "appsystem.h"

#include <string_view>

struct StudioRenderConfig
{
	float fEyeShiftX;	// eye X position
	float fEyeShiftY;	// eye Y position
	float fEyeShiftZ;	// eye Z position
	float fEyeSize;		// adjustment to iris textures
	float fEyeGlintPixelWidthLODThreshold;

	int maxDecalsPerModel;
	int drawEntities;
	int skin;
	int fullbright;

	bool bEyeMove : 1;		// look around
	bool bSoftwareSkin : 1;
	bool bNoHardware : 1;
	bool bNoSoftware : 1;
	bool bTeeth : 1;
	bool bEyes : 1;
	bool bFlex : 1;
	bool bWireframe : 1;
	bool bDrawNormals : 1;
	bool bDrawTangentFrame : 1;
	bool bDrawZBufferedWireframe : 1;
	bool bSoftwareLighting : 1;
	bool bShowEnvCubemapOnly : 1;
	bool bWireframeDecals : 1;

	// Reserved for future use
	int m_nReserved[4];
};

struct StudioRenderConfigInternal : public StudioRenderConfig
{
	bool m_bSupportsVertexAndPixelShaders : 1;
	bool m_bSupportsOverbright : 1;
	bool m_bEnableHWMorph : 1;
};

#define MAXLOCALLIGHTS 4
#define MAXLIGHTCOMPUTE 16
#define MAX_MAT_OVERRIDES 4

struct StudioRenderContext
{
	StudioRenderConfigInternal	m_Config;
	Vector					m_ViewTarget;
	Vector					m_ViewOrigin;
	Vector					m_ViewRight;
	Vector					m_ViewUp;
	Vector					m_ViewPlaneNormal;
	Vector4D				m_LightBoxColors[6];
	LightDesc				m_LocalLights[MAXLOCALLIGHTS];
	int						m_NumLocalLights;
	float					m_ColorMod[3];
	float					m_AlphaMod;
	Material* m_pForcedMaterial[MAX_MAT_OVERRIDES];
	OverrideType			m_nForcedMaterialType;
	int						m_nForcedMaterialIndex[MAX_MAT_OVERRIDES];
	int						m_nForcedMaterialIndexCount;
};

enum
{
	STUDIORENDER_DRAW_ENTIRE_MODEL = 0,
	STUDIORENDER_DRAW_OPAQUE_ONLY = 0x01,
	STUDIORENDER_DRAW_TRANSLUCENT_ONLY = 0x02,
	STUDIORENDER_DRAW_GROUP_MASK = 0x03,

	STUDIORENDER_DRAW_NO_FLEXES = 0x04,
	STUDIORENDER_DRAW_STATIC_LIGHTING = 0x08,

	STUDIORENDER_DRAW_ACCURATETIME = 0x10,		// Use accurate timing when drawing the model.
	STUDIORENDER_DRAW_NO_SHADOWS = 0x20,
	STUDIORENDER_DRAW_GET_PERF_STATS = 0x40,

	STUDIORENDER_DRAW_WIREFRAME = 0x80,

	STUDIORENDER_DRAW_ITEM_BLINK = 0x100,

	STUDIORENDER_SHADOWDEPTHTEXTURE = 0x200,

	STUDIORENDER_UNUSED = 0x400,

	STUDIORENDER_SKIP_DECALS = 0x800,

	STUDIORENDER_MODEL_IS_CACHEABLE = 0x1000,

	STUDIORENDER_SHADOWDEPTHTEXTURE_INCLUDE_TRANSLUCENT_MATERIALS = 0x2000,

	STUDIORENDER_NO_PRIMARY_DRAW = 0x4000,

	STUDIORENDER_SSAODEPTHTEXTURE = 0x8000,

};

#define MAX_DRAW_MODEL_INFO_MATERIALS 8

struct DrawModelResults
{
	int m_ActualTriCount;
	int m_TextureMemoryBytes;
	int m_NumHardwareBones;
	int m_NumBatches;
	int m_NumMaterials;
	int m_nLODUsed;
	int m_flLODMetric;
	//FastTimer m_RenderTime;
	//UtlVector<Material*, MAX_DRAW_MODEL_INFO_MATERIALS> m_Materials;
};

class StudioRender : public AppSystem
{
public:
	StudioRenderContext renderContext = { };

public:
	virtual void BeginFrame(void) = 0;
	virtual void EndFrame(void) = 0;

	// Used for the mat_stub console command.
	virtual void Mat_Stub(MaterialSystem* pMatSys) = 0;

	// Updates the rendering configuration
	virtual void UpdateConfig(const StudioRenderConfig& config) = 0;
	virtual void GetCurrentConfig(StudioRenderConfig& config) = 0;

	// Load, unload model data
	virtual bool LoadModel(StudioHdr* pStudioHdr, void* pVtxData, StudioHwData* pHardwareData) = 0;
	virtual void UnloadModel(StudioHwData* pHardwareData) = 0;

	// Refresh the studiohdr since it was lost...
	virtual void RefreshStudioHdr(StudioHdr* pStudioHdr, StudioHwData* pHardwareData) = 0;

	// This is needed to do eyeglint and calculate the correct texcoords for the eyes.
	virtual void SetEyeViewTarget(const StudioHdr* pStudioHdr, int nBodyIndex, const Vector& worldPosition) = 0;

	// Methods related to lighting state
	// NOTE: SetAmbientLightColors assumes that the arraysize is the same as
	// returned from GetNumAmbientLightSamples
	virtual int GetNumAmbientLightSamples() = 0;
	virtual const Vector* GetAmbientLightDirections() = 0;
	virtual void SetAmbientLightColors(const Vector4D* pAmbientOnlyColors) = 0;
	virtual void SetAmbientLightColors(const Vector* pAmbientOnlyColors) = 0;
	virtual void SetLocalLights(int numLights, const LightDesc* pLights) = 0;

	// Sets information about the camera location + orientation
	virtual void SetViewState(const Vector& viewOrigin, const Vector& viewRight,
		const Vector& viewUp, const Vector& viewPlaneNormal) = 0;

	// LOD stuff
	virtual int GetNumLODs(const StudioHwData& hardwareData) const = 0;
	virtual float GetLODSwitchValue(const StudioHwData& hardwareData, int lod) const = 0;
	virtual void SetLODSwitchValue(StudioHwData& hardwareData, int lod, float switchValue) = 0;

	// Sets the color/alpha modulation
	virtual void SetColorModulation(float const* pColor) = 0;
	virtual void SetAlphaModulation(float flAlpha) = 0;

	// Draws the model
	virtual void DrawModel(DrawModelResults* pResults, const DrawModelInfo& info,
		Matrix3x4* pBoneToWorld, float* pFlexWeights, float* pFlexDelayedWeights, const Vector& modelOrigin, int flags = STUDIORENDER_DRAW_ENTIRE_MODEL) = 0;

	// Methods related to static prop rendering
	virtual void DrawModelStaticProp(const DrawModelInfo& drawInfo, const Matrix3x4& modelToWorld, int flags = STUDIORENDER_DRAW_ENTIRE_MODEL) = 0;
	virtual void DrawStaticPropDecals(const DrawModelInfo& drawInfo, const Matrix3x4& modelToWorld) = 0;
	virtual void DrawStaticPropShadows(const DrawModelInfo& drawInfo, const Matrix3x4& modelToWorld, int flags) = 0;

	// Causes a material to be used instead of the materials the model was compiled with
	virtual void ForcedMaterialOverride(Material* newMaterial, OverrideType nOverrideType = OVERRIDE_NORMAL, int nMaterialIndex = -1) = 0;
	virtual bool IsForcedMaterialOverride() = 0;

	virtual StudioDecalHandle CreateDecalList(StudioHwData* pHardwareData) = 0;
	virtual void DestroyDecalList(StudioDecalHandle handle) = 0;

	// Add decals to a decal list by doing a planar projection along the ray
	// The BoneToWorld matrices must be set before this is called
	virtual void AddDecal(StudioDecalHandle handle, StudioHdr* pStudioHdr, Matrix3x4* pBoneToWorld,
		const Ray& ray, const Vector& decalUp, Material* pDecalMaterial, float radius, int body, bool noPokethru = false, int maxLODToDecal = ADDDECAL_TO_ALL_LODS, void* pvProxyUserData = NULL, int nAdditionalDecalFlags = 0) = 0;

	// Compute the lighting at a point and normal
	virtual void ComputeLighting(const Vector* pAmbient, int lightCount,
		LightDesc* pLights, const Vector& pt, const Vector& normal, Vector& lighting) = 0;

	// Compute the lighting at a point, constant directional component is passed
	// as flDirectionalAmount
	virtual void ComputeLightingConstDirectional(const Vector* pAmbient, int lightCount,
		LightDesc* pLights, const Vector& pt, const Vector& normal, Vector& lighting, float flDirectionalAmount) = 0;
};
