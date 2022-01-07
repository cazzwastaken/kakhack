#pragma once
#include "../definitions.h"

#include "../data/matrix.h"

enum BoneIndex : int
{
	BONE_INVALID = -1,
	BONE_PELVIS,
	BONE_LEAN_ROOT,
	BONE_CAM_DRIVER,
	BONE_SPINE_0,
	BONE_SPINE_1,
	BONE_SPINE_2,
	BONE_SPINE_3,
	BONE_NECK,
	BONE_HEAD,
	BONE_CLAVICLE_L,
	BONE_ARM_UPPER_L,
	BONE_ARM_LOWER_L,
	BONE_HAND_L,
	BONE_FINGER_MIDDLE_META_L,
	BONE_FINGER_MIDDLE_0_L,
	BONE_FINGER_MIDDLE_1_L,
	BONE_FINGER_MIDDLE_2_L,
	BONE_FINGER_PINKY_META_L,
	BONE_FINGER_PINKY_0_L,
	BONE_FINGER_PINKY_1_L,
	BONE_FINGER_PINKY_2_L,
	BONE_FINGER_INDEX_META_L,
	BONE_FINGER_INDEX_0_L,
	BONE_FINGER_INDEX_1_L,
	BONE_FINGER_INDEX_2_L,
	BONE_FINGER_THUMB_0_L,
	BONE_FINGER_THUMB_1_L,
	BONE_FINGER_THUMB_2_L,
	BONE_FINGER_RING_META_L,
	BONE_FINGER_RING_0_L,
	BONE_FINGER_RING_1_L,
	BONE_FINGER_RING_2_L,
	BONE_WEAPON_HAND_L,
	BONE_ARM_LOWER_L_TWIST,
	BONE_ARM_LOWER_L_TWIST1,
	BONE_ARM_UPPER_L_TWIST,
	BONE_ARM_UPPER_L_TWIST1,
	BONE_CLAVICLE_R,
	BONE_ARM_UPPER_R,
	BONE_ARM_LOWER_R,
	BONE_HAND_R,
	BONE_FINGER_MIDDLE_META_R,
	BONE_FINGER_MIDDLE_0_R,
	BONE_FINGER_MIDDLE_1_R,
	BONE_FINGER_MIDDLE_2_R,
	BONE_FINGER_PINKY_META_R,
	BONE_FINGER_PINKY_0_R,
	BONE_FINGER_PINKY_1_R,
	BONE_FINGER_PINKY_2_R,
	BONE_FINGER_INDEX_META_R,
	BONE_FINGER_INDEX_0_R,
	BONE_FINGER_INDEX_1_R,
	BONE_FINGER_INDEX_2_R,
	BONE_FINGER_THUMB_0_R,
	BONE_FINGER_THUMB_1_R,
	BONE_FINGER_THUMB_2_R,
	BONE_FINGER_RING_META_R,
	BONE_FINGER_RING_0_R,
	BONE_FINGER_RING_1_R,
	BONE_FINGER_RING_2_R,
	BONE_WEAPON_HAND_R,
	BONE_ARM_LOWER_R_TWIST,
	BONE_ARM_LOWER_R_TWIST1,
	BONE_ARM_UPPER_R_TWIST,
	BONE_ARM_UPPER_R_TWIST1,
	BONE_LEG_UPPER_L,
	BONE_LEG_LOWER_L,
	BONE_ANKLE_L,
	BONE_BALL_L,
	BONE_LFOOT_LOCK,
	BONE_LEG_UPPER_L_TWIST,
	BONE_LEG_UPPER_L_TWIST1,
	BONE_LEG_UPPER_R,
	BONE_LEG_LOWER_R,
	BONE_ANKLE_R,
	BONE_BALL_R,
	BONE_RFOOT_LOCK,
	BONE_LEG_UPPER_R_TWIST,
	BONE_LEG_UPPER_R_TWIST1,
	BONE_FINGER_PINKY_L_END,
	BONE_FINGER_PINKY_R_END,
	BONE_VALVEBIPED_WEAPON_BONE,
	BONE_LH_IK_DRIVER,
	BONE_PRIMARY_JIGGLE_JNT,
};

enum RenderFlags : unsigned int
{
	RENDER_FLAGS_DISABLE_RENDERING = 0x01,
	RENDER_FLAGS_HASCHANGED = 0x02,
	RENDER_FLAGS_ALTERNATE_SORTING = 0x04,
	RENDER_FLAGS_RENDER_WITH_VIEWMODELS = 0x08,
	RENDER_FLAGS_BLOAT_BOUNDS = 0x10,
	RENDER_FLAGS_BOUNDS_VALID = 0x20,
	RENDER_FLAGS_BOUNDS_ALWAYS_RECOMPUTE = 0x40,
	RENDER_FLAGS_IS_SPRITE = 0x80,
	RENDER_FLAGS_FORCE_OPAQUE_PASS = 0x100,
};

enum HitboxIndex : int
{
	HITBOX_INVALID = -1,
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_PELVIS,
	HITBOX_STOMACH,
	HITBOX_THORAX,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};

struct Model
{
	std::byte	pad0[0x4];		//0x0000
	char		name[260];	//0x0004
	int			loadFlags;		//0x0108
	int			serverCount;	//0x010C
	int			type;			//0x0110
	int			flags;			//0x0114
	Vector		mins;		//0x0118
	Vector		maxs;		//0x0124
	float		radius;		//0x0130
	std::byte	pad1[0x1C];		//0x0134
};

struct StudioBbox
{
	int bone;
	int group;
	Vector bbMin;
	Vector bbMax;
	int hitboxNameIndex;
	Vector offsetOrientation;
	float capsuleRadius;
	int	unused[4];

	inline const char* GetHitboxName() const
	{
		if (!hitboxNameIndex) return nullptr;
		return (const char*)this + hitboxNameIndex;
	}
};

struct StudioHitboxSet
{
	int nameIndex;
	int numHitboxes;
	int hitboxIndex;

	const char* GetName() noexcept
	{
		return nameIndex ? reinterpret_cast<const char*>(std::uintptr_t(this) + nameIndex) : nullptr;
	}

	StudioBbox* GetHitbox(int i) noexcept
	{
		return i >= 0 && i < numHitboxes ? reinterpret_cast<StudioBbox*>(std::uintptr_t(this) + hitboxIndex) + i : nullptr;
	}
};

struct StudioBone
{
	int nameIndex;
	int	parent;
	std::byte pad0[152];
	int flags;
	std::byte pad2[52];

	const char* GetName() const noexcept
	{
		return nameIndex ? reinterpret_cast<const char*>(std::uintptr_t(this) + nameIndex) : nullptr;
	}
};

struct StudioHdr
{
	int id;
	int version;
	int checksum;
	char name[64];
	int length;
	Vector eyePosition;
	Vector illumPosition;
	Vector hullMin;
	Vector hullMax;
	Vector bbMin;
	Vector bbMax;
	int flags;
	int numBones;
	int boneIndex;
	int numBoneControllers;
	int boneControllerIndex;
	int numHitboxSets;
	int hitboxSetIndex;
	int	localAnimations;
	int	localAnimationIndex;
	int localSequences;
	int localSequenceIndex;

	const StudioBone* GetBone(int i) const noexcept
	{
		return i >= 0 && i < numBones ? reinterpret_cast<StudioBone*>(uintptr_t(this) + boneIndex) + i : nullptr;
	}

	StudioHitboxSet* GetHitboxSet(int i) noexcept
	{
		return i >= 0 && i < numHitboxSets ? reinterpret_cast<StudioHitboxSet*>(uintptr_t(this) + hitboxSetIndex) + i : nullptr;
	}
};

enum RenderableTranslucencyType
{
	RENDERABLE_IS_OPAQUE = 0,
	RENDERABLE_IS_TRANSLUCENT,
	RENDERABLE_IS_TWO_PASS,	// has both translucent and opaque sub-partsa
};

using MDLHandle = unsigned short;

struct Collide;
struct VirtualModel;
struct CombinerModelInput;

class UtlBuffer;

class ModelLoadCallback
{
public:
	virtual void OnModelLoadComplete(const Model * pModel) = 0;

protected:
	// Protected destructor so that nobody tries to delete via this interface.
	// Automatically unregisters if the callback is destroyed while still pending.
	//~ModelLoadCallback();
};

class ModelInfo
{
public:
	virtual ~ModelInfo(void) { }

	virtual const Model* GetModel(int modelindex) const = 0;
	// Returns index of model by name
	virtual int						GetModelIndex(const char* name) const = 0;

	// Returns name of model
	virtual const char* GetModelName(const Model* model) const = 0;
	virtual void unknown0() = 0;
	virtual void unknown1() = 0;
	virtual Collide* GetVCollide(const Model* model) const = 0;
	virtual Collide* GetVCollide(int modelindex) const = 0;
	virtual void					GetModelBounds(const Model* model, Vector& mins, Vector& maxs) const = 0;
	virtual	void					GetModelRenderBounds(const Model* model, Vector& mins, Vector& maxs) const = 0;
	virtual int						GetModelFrameCount(const Model* model) const = 0;
	virtual int						GetModelType(const Model* model) const = 0;
	virtual void* GetModelExtraData(const Model* model) = 0;
	virtual bool					ModelHasMaterialProxy(const Model* model) const = 0;
	virtual bool					IsTranslucent(Model const* model) const = 0;
	virtual bool					IsTranslucentTwoPass(const Model* model) const = 0;
	virtual void					Unused0() {};
	virtual RenderableTranslucencyType ComputeTranslucencyType(const Model* model, int nSkin, int nBody) = 0;
	virtual int						GetModelMaterialCount(const Model* model) const = 0;
	virtual int 					GetModelMaterials(const Model* model, int count, Material** ppMaterial) = 0;
	virtual bool					IsModelVertexLit(const Model* model) const = 0;
	virtual const char* GetModelKeyValueText(const Model* model) = 0;
	virtual bool					GetModelKeyValue(const Model* model, UtlBuffer& buf) = 0; // supports keyvalue blocks in submodels
	virtual float					GetModelRadius(const Model* model) = 0;

	virtual const StudioHdr* FindModel(const StudioHdr* pStudioHdr, void** cache, const char* modelname) const = 0;
	virtual const StudioHdr* FindModel(void* cache) const = 0;
	virtual	VirtualModel* GetVirtualModel(const StudioHdr* pStudioHdr) const = 0;
	virtual std::byte* GetAnimBlock(const StudioHdr* pStudioHdr, int nBlock, bool bPreloadIfMissing) const = 0;
	virtual bool					HasAnimBlockBeenPreloaded(const StudioHdr* pStudioHdr, int nBlock) const = 0;

	// Available on client only!!!
	virtual void					GetModelMaterialColorAndLighting(const Model* model, Vector const& origin,
		Vector const& angles, Trace* pTrace,
		Vector& lighting, Vector& matColor) = 0;
	virtual void					GetIlluminationPoint(const Model* model, ClientRenderable* pRenderable, Vector const& origin,
		Vector const& angles, Vector* pLightingCenter) = 0;

	virtual int						GetModelContents(int modelIndex) const = 0;
	virtual StudioHdr* GetStudiomodel(const Model* mod) = 0;
	virtual int						GetModelSpriteWidth(const Model* model) const = 0;
	virtual int						GetModelSpriteHeight(const Model* model) const = 0;

	// Sets/gets a map-specified fade range (client only)
	virtual void					SetLevelScreenFadeRange(float flMinSize, float flMaxSize) = 0;
	virtual void					GetLevelScreenFadeRange(float* pMinArea, float* pMaxArea) const = 0;

	// Sets/gets a map-specified per-view fade range (client only)
	virtual void					SetViewScreenFadeRange(float flMinSize, float flMaxSize) = 0;

	// Computes fade alpha based on distance fade + screen fade (client only)
	virtual unsigned char			ComputeLevelScreenFade(const Vector& vecAbsOrigin, float flRadius, float flFadeScale) const = 0;
	virtual unsigned char			ComputeViewScreenFade(const Vector& vecAbsOrigin, float flRadius, float flFadeScale) const = 0;

	// both client and server
	virtual int						GetAutoplayList(const StudioHdr* pStudioHdr, unsigned short** pAutoplayList) const = 0;

	// Gets a virtual terrain collision model (creates if necessary)
	// NOTE: This may return NULL if the terrain model cannot be virtualized
	virtual PhysCollide* GetCollideForVirtualTerrain(int index) = 0;

	virtual bool					IsUsingFBTexture(const Model* model, int nSkin, int nBody, void /*IClientRenderable*/* pClientRenderable) const = 0;

	virtual const Model* FindOrLoadModel(const char* name) const = 0;

	virtual MDLHandle			GetCacheHandle(const Model* model) const = 0;

	// Returns planes of non-nodraw brush model surfaces
	virtual int						GetBrushModelPlaneCount(const Model* model) const = 0;
	virtual void					GetBrushModelPlane(const Model* model, int nIndex, CPlane& plane, Vector* pOrigin) const = 0;
	virtual int						GetSurfacepropsForVirtualTerrain(int index) = 0;
	virtual bool					UsesEnvCubemap(const Model* model) const = 0;
	virtual bool					UsesStaticLighting(const Model* model) const = 0;

	// Returns index of model by name, dynamically registered if not already known.
	virtual int						RegisterDynamicModel(const char* name, bool bClientSide) = 0;
	virtual int						RegisterCombinedDynamicModel(const char* pszName, MDLHandle Handle) = 0;
	virtual void					UpdateCombinedDynamicModel(int nModelIndex, MDLHandle Handle) = 0;

	virtual int						BeginCombinedModel(const char* pszName, bool bReuseExisting) = 0;
	virtual bool					SetCombineModels(int nModelIndex, const UtlVector< CombinerModelInput >& vecModelsToCombine) = 0;
	virtual bool					FinishCombinedModel(int nModelIndex, void* pFunc, void* pUserData = NULL) = 0;
	virtual void					ReleaseCombinedModel(int nModelIndex) = 0;

	virtual bool					IsDynamicModelLoading(int modelIndex) = 0;
	virtual void					AddRefDynamicModel(int modelIndex) = 0;
	virtual void					ReleaseDynamicModel(int modelIndex) = 0;

	// Registers callback for when dynamic model has finished loading.
	virtual bool					RegisterModelLoadCallback(int modelindex, ModelLoadCallback* pCallback, bool bCallImmediatelyIfLoaded = true) = 0;
	virtual void					UnregisterModelLoadCallback(int modelindex, ModelLoadCallback* pCallback) = 0;

	// Poked by engine
	virtual void					OnLevelChange() = 0;

	virtual KeyValues* GetModelKeyValues(const Model* pModel) = 0;

	virtual void					UpdateViewWeaponModelCache(const char** ppWeaponModels, int nWeaponModels) = 0;
	virtual void					TouchWorldWeaponModelCache(const char** ppWeaponModels, int nWeaponModels) = 0;
};

class ModelInfoClient : public ModelInfo
{
public:
	// Returns a model as a client-side index which is stable across server changes
	virtual int						GetModelClientSideIndex(const char* name) const = 0;

	// Poked by engine
	virtual void					OnDynamicModelStringTableChanged(int nStringIndex, const char* pString, const void* pData) = 0;

	// Reference and Unload
	// Don't assume Reference flags - doing this for now
	virtual Model* ReferenceModel(const char* name) = 0;
	virtual void					UnreferenceModel(Model* model) = 0;
	virtual void					UnloadUnreferencedModels(void) = 0;

	virtual void unknown2() = 0;
	virtual void unknown3() = 0;
};
