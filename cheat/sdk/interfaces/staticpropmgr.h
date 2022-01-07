#pragma once
#include "../definitions.h"

#include "../entity/clientrenderable.h"
#include "../entity/staticprop.h"

#include "../data/vector.h"
#include "../data/utlvector.h"

struct LightCacheHandle;

class StaticPropMgrEngine
{
public:
	virtual bool Init() = 0;
	virtual void Shutdown() = 0;

	// Call at the beginning of the level, will unserialize all static
	// props and add them to the main collision tree
	virtual void LevelInit() = 0;

	// Call this when there's a client, *after* LevelInit, and after the world entity is loaded
	virtual void LevelInitClient() = 0;

	// Call this when there's a client, *before* LevelShutdown
	virtual void LevelShutdownClient() = 0;

	// Call at the end of the level, cleans up the static props
	virtual void LevelShutdown() = 0;

	// Call this to recompute static prop lighting when necessary
	virtual void RecomputeStaticLighting() = 0;

	// Check if a static prop is in a particular PVS.
	virtual bool IsPropInPVS(HandleEntity* pHandleEntity, const std::byte* pVis) const = 0;

	// temp - loadtime setting of flag to disable CSM rendering for static prop.
	virtual void DisableCSMRenderingForStaticProp(int staticPropIndex) = 0;

	// returns a collideable interface to static props
	virtual Collideable* GetStaticProp(HandleEntity* pHandleEntity) = 0;

	// returns the lightcache handle associated with a static prop
	virtual LightCacheHandle GetLightCacheHandleForStaticProp(HandleEntity* pHandleEntity) = 0;

	// Is a base handle a static prop?
	virtual bool IsStaticProp(HandleEntity* pHandleEntity) const = 0;
	virtual bool IsStaticProp(BaseHandle handle) const = 0;

	// Returns the static prop index (useful for networking)
	virtual int GetStaticPropIndex(HandleEntity* pHandleEntity) const = 0;

	virtual void ConfigureSystemLevel(int nCPULevel, int nGPULevel) = 0;

	virtual void RestoreStaticProps() = 0;
	virtual void Unknown() = 0;
};

class PhysicsEnvironment;
class PhysicsKeyHandler;

class StaticPropMgr
{
public:
	// Create physics representations of props
	virtual void	CreateVPhysicsRepresentations(PhysicsEnvironment * physenv, PhysicsKeyHandler * pDefaults, void* pGameData) = 0;

	// Purpose: Trace a ray against the specified static Prop. Returns point of intersection in trace_t
	virtual void	TraceRayAgainstStaticProp(const Ray& ray, int staticPropIndex, Trace& tr) = 0;

	// Is a base handle a static prop?
	virtual bool	IsStaticProp(HandleEntity* pHandleEntity) const = 0;
	virtual bool	IsStaticProp(BaseHandle handle) const = 0;

	// returns a collideable interface to static props
	virtual Collideable* GetStaticPropByIndex(int propIndex) = 0;
};

class StaticPropMgrClient : public StaticPropMgr
{
public:
	// Adds decals to static props, returns point of decal in trace_t
	virtual void	AddDecalToStaticProp(const Vector & rayStart, const Vector & rayEnd,
		int staticPropIndex, int decalIndex, bool doTrace, Trace& tr, void* pvProxyUserData = NULL, const Vector * saxis = NULL, int nAdditionalDecalFlags = 0) = 0;

	// Adds/removes shadows from static props
	virtual void	AddShadowToStaticProp(unsigned short shadowHandle, ClientRenderable* pRenderable) = 0;
	virtual void	RemoveAllShadowsFromStaticProp(ClientRenderable* pRenderable) = 0;

	// Gets the lighting + material color of a static prop
	virtual void	GetStaticPropMaterialColorAndLighting(Trace* pTrace,
		int staticPropIndex, Vector& lighting, Vector& matColor) = 0;

	//Changes made specifically to support the Portal mod (smack Dave Kircher if something breaks) (Added separately to both client and server to not mess with versioning)
	//===================================================================
	virtual void GetAllStaticProps(UtlVector<Collideable*>* pOutput) = 0; //testing function that will eventually be removed
	virtual void GetAllStaticPropsInAABB(const Vector& vMins, const Vector& vMaxs, UtlVector<Collideable*>* pOutput) = 0; //get all static props that exist wholly or partially in an AABB
	virtual void GetAllStaticPropsInOBB(const Vector& ptOrigin, const Vector& vExtent1, const Vector& vExtent2, const Vector& vExtent3, UtlVector<Collideable*>* pOutput) = 0; //get all static props that exist wholly or partially in an OBB
	//===================================================================

	virtual void DrawStaticProps(ClientRenderable** pProps, const RenderableInstance* pInstances, int count, bool bShadowDepth, bool drawVCollideWireframe) = 0;

	// Returns the lighting origins of a number of static props
	virtual void GetLightingOrigins(Vector* pLightingOrigins, int nOriginStride, int nCount, ClientRenderable** ppRenderable, int nRenderableStride) = 0;
};

struct StaticPropLump
{
	Vector			m_Origin;
	Vector			m_Angles;
	unsigned short	m_PropType;
	unsigned short	m_FirstLeaf;
	unsigned short	m_LeafCount;
	unsigned char	m_Solid;
	unsigned char	m_Flags;
	int				m_Skin;
	float			m_FadeMinDist;
	float			m_FadeMaxDist;
	Vector			m_LightingOrigin;
	float			m_flForcedFadeScale;
	unsigned char	m_nMinCPULevel;
	unsigned char	m_nMaxCPULevel;
	unsigned char	m_nMinGPULevel;
	unsigned char	m_nMaxGPULevel;
	//	int				m_Lighting;			// index into the GAMELUMP_STATIC_PROP_LIGHTING lump
	Color			m_DiffuseModulation;	// per instance color and alpha modulation
	bool			m_bDisableX360;
	int				m_FlagsEx;				// more flags (introduced in v10)
};

struct StaticPropLeafLump
{
	unsigned short	m_Leaf;
};

class StaticPropManager : public StaticPropMgrEngine, public StaticPropMgrClient
{
public:
	UtlVector <Model*> staticPropDict;
	UtlVector <StaticProp> props;
	UtlVector <StaticPropLeafLump> staticPropLeaves;
};

