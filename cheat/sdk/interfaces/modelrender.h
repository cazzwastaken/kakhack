#pragma once
#include "modelinfo.h"
#include "texture.h"

constexpr auto MATERIAL_MAX_LIGHT_COUNT = 4;

DECLARE_POINTER_HANDLE(StudioDecalHandle);

class StudioHwData;
struct StudioHdr;

struct LightCacheHandle;
struct ColorMeshInfo;
struct MemHandle;
using DataCacheHandle = MemHandle;


struct RenderableInfo
{
	ClientRenderable* renderable;		// 0x00
	ClientAlphaProperty* alphaProperty;		// 0x04
	int enumCount;			// 0x08
	int renderFrame;		// 0x0C
	unsigned short firstShadow;		// 0x10
	unsigned short leafList;			// 0x12
	short area;				// 0x14
	uint16_t flags;				// 0x16
	uint16_t flags2;			// 0x18
	Vector bloatedAbsMins;	// 0x1A
	Vector bloatedAbsMaxs;	// 0x26
	Vector mins;			// 0x32
	Vector maxs;			// 0x3E
	std::byte pad0[0x4];			// 0x4A
}; // Size: 0x4E


enum LightType
{
	MATERIAL_LIGHT_DISABLE = 0,
	MATERIAL_LIGHT_POINT,
	MATERIAL_LIGHT_DIRECTIONAL,
	MATERIAL_LIGHT_SPOT,
};

struct LightDesc
{
	LightType type;										//< MATERIAL_LIGHT_xxx
	Vector color;											//< color+intensity
	Vector position;										//< light source center position
	Vector direction;										//< for SPOT, direction it is pointing
	float  range;											//< distance range for light.0=infinite
	float falloff;										//< angular falloff exponent for spot lights
	float attenuation0;									//< constant distance falloff term
	float attenuation1;									//< linear term of falloff
	float attenuation2;									//< quadatic term of falloff

	// NOTE: theta and phi are *half angles*
	float theta;											//< inner cone angle. no angular falloff
															//< within this cone
	float phi;											//< outer cone angle

	// the values below are derived from the above settings for optimizations
	// These aren't used by DX8. . used for software lighting.

	// NOTE: These dots are cos( m_Theta ), cos( m_Phi )
	float thetaDot;
	float phiDot;
	float oneOverThetaDotMinusPhiDot;
	unsigned int flags;
protected:
	float rangeSquared;
};

struct MaterialLightingState
{
	Vector			ambientCube[6];		// ambient, and lights that aren't in locallight[]
	Vector			lightingOrigin;		// The position from which lighting state was computed
	int				localLightCount;
	LightDesc		localLightDesc[MATERIAL_MAX_LIGHT_COUNT];
};

struct DrawModelState
{
	StudioHdr* studioHdr;
	StudioHwData* studioHWData;
	ClientRenderable* renderable;
	const Matrix3x4* modelToWorld;
	StudioDecalHandle decals;
	int drawFlags;
	int lod;
};

struct DrawModelInfo
{
	StudioHdr* studioHdr;
	StudioHwData* hardwareData;
	StudioDecalHandle		decals;
	int						skin;
	int						body;
	int						hitboxSet;
	ClientRenderable* clientEntity;
	int						lod;
	ColorMeshInfo* colorMeshes;
	bool					staticLighting;
	MaterialLightingState lightingState;
};

using ModelInstanceHandle = unsigned short;
enum
{
	MODEL_INSTANCE_INVALID = (ModelInstanceHandle)~0
};

struct ModelRenderInfo
{
	Vector origin;
	Vector angles;
	std::byte pad0[0x4];
	ClientRenderable* renderable;
	const Model* model;
	const Matrix3x4* modelToWorld;
	const Matrix3x4* lightingOffset;
	const Vector* lightingOrigin;
	int flags;
	int entityIndex;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle instance;
};

struct StaticPropRenderInfo
{
	const Matrix3x4* modelToWorld;
	const Model* model;
	ClientRenderable* renderable;
	Vector* lightingOrigin;
	ModelInstanceHandle	instance;
	uint8_t skin;
	uint8_t alpha;
};

struct LightingQuery
{
	Vector lightingOrigin;
	ModelInstanceHandle instanceHandle;
	bool ambientBoost;
};

struct StaticLightingQuery : public LightingQuery
{
	ClientRenderable* m_pRenderable;
};

enum
{
	ADDDECAL_TO_ALL_LODS = -1
};

class MatRenderContext;
class ModelRender
{
public:
	virtual int		DrawModel(int flags,
		ClientRenderable* renderable,
		ModelInstanceHandle instance,
		int entityIndex,
		const Model* model,
		Vector const& origin,
		Vector const& angles,
		int skin,
		int body,
		int hitboxset,
		const Matrix3x4* modelToWorld = NULL,
		const Matrix3x4* lightingOffset = NULL) = 0;

	// This causes a material to be used when rendering the model instead
	// of the materials the model was compiled with
	virtual void	ForcedMaterialOverride(Material* newMaterial, OverrideType nOverrideType = OVERRIDE_NORMAL, int nMaterialIndex = -1) = 0;
	virtual bool	IsForcedMaterialOverride() = 0;

	virtual void	SetViewTarget(const StudioHdr* pStudioHdr, int nBodyIndex, const Vector& target) = 0;

	// Creates, destroys instance data to be associated with the model
	virtual ModelInstanceHandle CreateInstance(ClientRenderable* pRenderable, LightCacheHandle* pCache = NULL) = 0;
	virtual void DestroyInstance(ModelInstanceHandle handle) = 0;

	// Associates a particular lighting condition with a model instance handle.
	// FIXME: This feature currently only works for static props. To make it work for entities, etc.,
	// we must clean up the lightcache handles as the model instances are removed.
	// At the moment, since only the static prop manager uses this, it cleans up all LightCacheHandles
	// at level shutdown.
	virtual void SetStaticLighting(ModelInstanceHandle handle, LightCacheHandle* pHandle) = 0;
	virtual LightCacheHandle GetStaticLighting(ModelInstanceHandle handle) = 0;

	// moves an existing InstanceHandle to a nex Renderable to keep decals etc. Models must be the same
	virtual bool ChangeInstance(ModelInstanceHandle handle, ClientRenderable* pRenderable) = 0;

	// Creates a decal on a model instance by doing a planar projection
	// along the ray. The material is the decal material, the radius is the
	// radius of the decal to create.
	virtual void AddDecal(ModelInstanceHandle handle, Ray const& ray,
		Vector const& decalUp, int decalIndex, int body, bool noPokeThru = false, int maxLODToDecal = ADDDECAL_TO_ALL_LODS, Material* pSpecifyMaterial = NULL, float w = 1.0f, float h = 1.0f, void* pvProxyUserData = NULL, int nAdditionalDecalFlags = 0) = 0;

	// Removes all the decals on a model instance
	virtual void RemoveAllDecals(ModelInstanceHandle handle) = 0;

	// Returns true if the model instance is valid and the decal list is not empty
	virtual bool ModelHasDecals(ModelInstanceHandle handle) = 0;

	// Remove all decals from all models
	virtual void RemoveAllDecalsFromAllModels(bool bRenderContextValid) = 0;

	// Shadow rendering, DrawModelShadowSetup returns the address of the bone-to-world array, NULL in case of error
	virtual Matrix3x4* DrawModelShadowSetup(ClientRenderable* pRenderable, int body, int skin, DrawModelInfo* pInfo, Matrix3x4* pCustomBoneToWorld = NULL) = 0;
	virtual void DrawModelShadow(ClientRenderable* pRenderable, const DrawModelInfo& info, Matrix3x4* pCustomBoneToWorld = NULL) = 0;

	// This gets called when overbright, etc gets changed to recompute static prop lighting.
	virtual bool RecomputeStaticLighting(ModelInstanceHandle handle) = 0;

	virtual void ReleaseAllStaticPropColorData(void) = 0;
	virtual void RestoreAllStaticPropColorData(void) = 0;

	// Extended version of drawmodel
	virtual int	DrawModelEx(ModelRenderInfo& pInfo) = 0;

	virtual int	DrawModelExStaticProp(MatRenderContext* pRenderContext, ModelRenderInfo& pInfo) = 0;

	virtual bool DrawModelSetup(MatRenderContext* pRenderContext, ModelRenderInfo& pInfo, DrawModelState* pState, Matrix3x4** ppBoneToWorldOut) = 0;
	virtual void DrawModelExecute(MatRenderContext* pRenderContext, const DrawModelState& state, const ModelRenderInfo& pInfo, Matrix3x4* pCustomBoneToWorld = NULL) = 0;

	// Sets up lighting context for a point in space
	virtual void SetupLighting(const Vector& vecCenter) = 0;

	// doesn't support any debug visualization modes or other model options, but draws static props in the
	// fastest way possible
	virtual int DrawStaticPropArrayFast(StaticPropRenderInfo* pProps, int count, bool bShadowDepth) = 0;

	// Allow client to override lighting state
	virtual void SuppressEngineLighting(bool bSuppress) = 0;

	virtual void SetupColorMeshes(int nTotalVerts) = 0;

	// Sets up lighting context for a point in space, with smooth interpolation per model.
	// Passing MODEL_INSTANCE_INVALID as a handle is equivalent to calling SetupLighting.
	virtual void SetupLightingEx(const Vector& vecCenter, ModelInstanceHandle handle) = 0;

	// Finds the brightest light source illuminating a point. Returns false if there isn't any.
	virtual bool GetBrightestShadowingLightSource(const Vector& vecCenter, Vector& lightPos, Vector& lightBrightness, bool bAllowNonTaggedLights) = 0;

	// Computes lighting state for an array of lighting requests
	virtual void ComputeLightingState(int nCount, const LightingQuery* pQuery, MaterialLightingState* pState, Texture** ppEnvCubemapTexture) = 0;

	// Gets an array of decal handles given model instances
	virtual void GetModelDecalHandles(StudioDecalHandle* pDecals, int nDecalStride, int nCount, const ModelInstanceHandle* pHandles) = 0;

	// Computes lighting state for an array of lighting requests for renderables which use static lighting
	virtual void ComputeStaticLightingState(int nCount, const StaticLightingQuery* pQuery, MaterialLightingState* pState, MaterialLightingState* pDecalState, ColorMeshInfo** ppStaticLighting, Texture** ppEnvCubemapTexture, DataCacheHandle* pColorMeshHandles) = 0;

	// Cleans up lighting state. Must be called after the draw call that uses
	// the color meshes return from ComputeStaticLightingState has been issued
	virtual void CleanupStaticLightingState(int nCount, DataCacheHandle* pColorMeshHandles) = 0;
};
