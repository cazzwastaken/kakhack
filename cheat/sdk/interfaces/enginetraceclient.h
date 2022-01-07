#pragma once
#include "../definitions.h"
#include "../data/vector.h"

#include "../entity/entity.h"


#define CONTENTS_EMPTY					0
#define CONTENTS_SOLID					0x1
#define CONTENTS_WINDOW					0x2
#define CONTENTS_AUX					0x4
#define CONTENTS_GRATE					0x8
#define CONTENTS_SLIME					0x10
#define CONTENTS_WATER					0x20
#define CONTENTS_BLOCKLOS				0x40
#define CONTENTS_OPAQUE					0x80
#define CONTENTS_TESTFOGVOLUM			0x100
#define CONTENTS_UNUSED					0x200
#define CONTENTS_BLOCKLIGHT				0x400
#define CONTENTS_TEAM1					0x800
#define CONTENTS_TEAM2					0x1000
#define CONTENTS_IGNORE_NODRAW_OPAQUE	0x2000
#define CONTENTS_MOVEABLE				0x4000
#define CONTENTS_AREAPORTAL				0x8000
#define CONTENTS_PLAYERCLIP				0x10000
#define CONTENTS_MONSTERCLIP			0x20000
#define CONTENTS_CURRENT_0				0x40000
#define CONTENTS_CURRENT_90				0x80000
#define CONTENTS_CURRENT_180			0x100000
#define CONTENTS_CURRENT_270			0x200000
#define CONTENTS_CURRENT_UP				0x400000
#define CONTENTS_CURRENT_DOWN			0x800000
#define CONTENTS_ORIGIN					0x1000000
#define CONTENTS_MONSTER				0x2000000
#define CONTENTS_DEBRIS					0x4000000
#define CONTENTS_DETAIL					0x8000000
#define CONTENTS_TRANSLUCENT			0x10000000
#define CONTENTS_LADDER					0x20000000
#define CONTENTS_HITBOX					0x40000000
#define LAST_VISIBLE_CONTENTS			CONTENTS_OPAQUE
#define ALL_VISIBLE_CONTENTS			(LAST_VISIBLE_CONTENTS | (LAST_VISIBLE_CONTENTS-1))

#define SURF_LIGHT						0x0001
#define SURF_SKY2D						0x0002
#define SURF_SKY						0x0004
#define SURF_WARP						0x0008
#define SURF_TRANS						0x0010
#define SURF_NOPORTAL					0x0020
#define SURF_TRIGGER					0x0040
#define SURF_NODRAW						0x0080
#define SURF_HINT						0x0100
#define SURF_SKIP						0x0200
#define SURF_NOLIGHT					0x0400
#define SURF_BUMPLIGHT					0x0800
#define SURF_NOSHADOWS					0x1000
#define SURF_NODECALS					0x2000
#define SURF_NOCHOP						0x4000
#define SURF_HITBOX						0x8000

#define MASK_ALL						(0xFFFFFFFF)
#define MASK_SOLID						(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_PLAYERSOLID				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_NPCSOLID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER|CONTENTS_GRATE)
#define MASK_NPCFLUID					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTERCLIP|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define MASK_WATER						(CONTENTS_WATER|CONTENTS_MOVEABLE|CONTENTS_SLIME)
#define MASK_OPAQUE						(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_OPAQUE)
#define MASK_OPAQUE_AND_NPCS			(MASK_OPAQUE|CONTENTS_MONSTER)
#define MASK_BLOCKLOS					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_BLOCKLOS)
#define MASK_BLOCKLOS_AND_NPCS			(MASK_BLOCKLOS|CONTENTS_MONSTER)
#define MASK_VISIBLE					(MASK_OPAQUE|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define MASK_VISIBLE_AND_NPCS			(MASK_OPAQUE_AND_NPCS|CONTENTS_IGNORE_NODRAW_OPAQUE)
#define MASK_SHOT						(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define MASK_SHOT_BRUSHONLY				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_DEBRIS)
#define MASK_SHOT_HULL					(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_MONSTER|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_GRATE)
#define MASK_SHOT_PORTAL				(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTER)
#define MASK_SOLID_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_GRATE)
#define MASK_PLAYERSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_PLAYERCLIP|CONTENTS_GRATE)
#define MASK_NPCSOLID_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_MOVEABLE|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define MASK_NPCWORLDSTATIC				(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP|CONTENTS_GRATE)
#define MASK_NPCWORLDSTATIC_FLUID		(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_MONSTERCLIP)
#define MASK_SPLITAREAPORTAL			(CONTENTS_WATER|CONTENTS_SLIME)
#define MASK_CURRENT					(CONTENTS_CURRENT_0|CONTENTS_CURRENT_90|CONTENTS_CURRENT_180|CONTENTS_CURRENT_270|CONTENTS_CURRENT_UP|CONTENTS_CURRENT_DOWN)
#define MASK_DEADSOLID					(CONTENTS_SOLID|CONTENTS_PLAYERCLIP|CONTENTS_WINDOW|CONTENTS_GRATE)

enum DispSurfFlags : int
{
	DISPSURF_FLAG_SURFACE = (1 << 0),
	DISPSURF_FLAG_WALKABLE = (1 << 1),
	DISPSURF_FLAG_BUILDABLE = (1 << 2),
	DISPSURF_FLAG_SURFPROP1 = (1 << 3),
	DISPSURF_FLAG_SURFPROP2 = (1 << 4)
};

enum TraceType : int
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,
	TRACE_ENTITIES_ONLY,
	TRACE_EVERYTHING_FILTER_PROPS,
	TRACE_FILTERSKY
};

enum DebugTraceCounterBehavior : int
{
	TRACE_COUNTER_SET = 0,
	TRACE_COUNTER_INC,
};

struct BrushSideInfo
{
	VectorAligned	plane;	// the plane of the brush side
	uint16_t	bevel;		// bevel plane?
	uint16_t	thin;		// thin?
};

struct CPlane
{
	Vector		normal;
	float		distance;
	std::byte	type;
	std::byte	signBits;
	std::byte	pad[0x2];
};

struct CSurface
{
	const char* name;
	short			surfaceProps;
	std::uint16_t	flags;
};

#define DISPSURF_FLAG_SURFACE		(1<<0)
#define DISPSURF_FLAG_WALKABLE		(1<<1)
#define DISPSURF_FLAG_BUILDABLE		(1<<2)
#define DISPSURF_FLAG_SURFPROP1		(1<<3)
#define DISPSURF_FLAG_SURFPROP2		(1<<4)
#define DISPSURF_FLAG_SURFPROP3		(1<<5)
#define DISPSURF_FLAG_SURFPROP4		(1<<6)

class TraceFilterInterface
{
public:
	virtual bool ShouldHitEntity(HandleEntity* pEntity, int contentsMask) = 0;
	virtual TraceType	GetTraceType() const = 0;
};

class TraceFilter : public TraceFilterInterface
{
	using FilterCallbackFn = bool(*)(HandleEntity*, int);

public:
	TraceFilter(const HandleEntity* skip, TraceType type = TraceType::TRACE_EVERYTHING)
		: skip(skip), type(type) { }

	bool ShouldHitEntity(HandleEntity* entity, int mask) override
	{
		return entity != skip;
	}

	TraceType GetTraceType() const override
	{
		return type;
	}

private:
	const HandleEntity* skip = nullptr;
	FilterCallbackFn checkCallback = nullptr;
	TraceType type = TraceType::TRACE_EVERYTHING;
};

class BaseTrace
{
public:

	// Displacement flags tests.
	bool IsDispSurface(void) { return ((dispFlags & DISPSURF_FLAG_SURFACE) != 0); }
	bool IsDispSurfaceWalkable(void) { return ((dispFlags & DISPSURF_FLAG_WALKABLE) != 0); }
	bool IsDispSurfaceBuildable(void) { return ((dispFlags & DISPSURF_FLAG_BUILDABLE) != 0); }
	bool IsDispSurfaceProp1(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP1) != 0); }
	bool IsDispSurfaceProp2(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP2) != 0); }
	bool IsDispSurfaceProp3(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP3) != 0); }
	bool IsDispSurfaceProp4(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP4) != 0); }

public:

	// these members are aligned!!
	Vector			startpos;				// start position
	Vector			endpos;					// final position
	CPlane		plane;					// surface normal at impact

	float			fraction;				// time completed, 1.0 = didn't hit anything

	int				contents;				// contents on other side of surface hit
	unsigned short	dispFlags;				// displacement flags for marking surfaces with data

	bool			allsolid;				// if true, plane is not valid
	bool			startsolid;				// if true, the initial point was in a solid area

	BaseTrace() {}

private:
	// No copy constructors allowed
	BaseTrace(const BaseTrace& vOther);
};

class Trace : public BaseTrace
{
public:
	// Gets the entity's network index if the trace has hit an entity.
	// If not, returns -1.
	inline int GetEntityIndex() const
	{
		if (entity)
			return entity->Index();
		else
			return -1;
	}

	// Returns true if there was any kind of impact at all
	inline bool DidHit() const
	{
		return fraction < 1.f || allsolid || startsolid;
	}

	inline bool IsVisible() const
	{
		return (fraction > 0.97f);
	}


public:

	float			fractionleftsolid;	// time we left a solid, only valid if we started in solid
	CSurface		surface;			// surface hit (impact surface)

	int				hitgroup;			// 0 == generic, non-zero is specific body part

	short			physicsbone;		// physics bone hit by trace in studio
	unsigned short	worldSurfaceIndex;	// Index of the msurface2_t, if applicable

	BaseEntity* entity;

	// NOTE: this member is overloaded.
	// If entity points at the world entity, then this is the static prop index.
	// Otherwise, this is the hitbox index.
	int			hitbox;					// box hit by trace in studio

	Trace() : entity(NULL) {}

private:
	// No copy constructors allowed
	Trace(const Trace& other);
};


//=============================================================================

class TraceListData
{
public:
	virtual ~TraceListData() {}

	virtual void Reset() = 0;
	virtual bool IsEmpty() = 0;
	// CanTraceRay will return true if the current volume encloses the ray
	// NOTE: The leaflist trace will NOT check this.  Traces are intersected
	// against the culled volume exclusively.
	virtual bool CanTraceRay(const Ray& ray) = 0;
};

struct Ray
{
	VectorAligned  start;	// starting point, centered within the extents
	VectorAligned  delta;	// direction + length of the ray
	VectorAligned  startOffset;	// Add this to m_Start to get the actual ray start
	VectorAligned  extents;	// Describes an axis aligned box extruded along a ray
	const Matrix3x4* worldAxisTransform;
	bool	isRay;	// are the extents zero?
	bool	isSwept;	// is delta != 0?

	Ray() : worldAxisTransform(NULL) {}

	Ray(Vector const& start, Vector const& end) :
		start(start), delta(end - start)
	{
		this->isSwept = (delta.LengthSqr() != 0);
		this->worldAxisTransform = NULL;
		this->isRay = true;
	}

	Ray(Vector const& start, Vector const& end, Vector const& mins, Vector const& maxs) :
		start(start), delta(end - start)
	{
		this->isSwept = (delta.LengthSqr() != 0);
		this->worldAxisTransform = NULL;

		this->extents = maxs - mins;
		this->extents *= 0.5f;

		this->isRay = (this->extents.LengthSqr() < 1e-6);

		if (this->extents.x >= 0 && this->extents.y >= 0 && this->extents.z >= 0)
		{
			this->startOffset = mins + maxs;
			this->startOffset += 0.5f;
			this->start = this->startOffset + start;
			this->startOffset *= -1.f;
		}
	}

	// compute inverse delta
	Vector InvDelta() const
	{
		Vector invDelta;
		for (int axis = 0; axis < 3; ++axis)
		{
			if (delta[axis] != 0.0f)
			{
				invDelta[axis] = 1.0f / delta[axis];
			}
			else
			{
				invDelta[axis] = FLT_MAX;
			}
		}
		return invDelta;
	}
};

class BrushQuery
{
public:
	BrushQuery(void)
	{
		m_iCount = 0;
		m_pBrushes = NULL;
		m_iMaxBrushSides = 0;
		m_pReleaseFunc = NULL;
		m_pData = NULL;
	}
	~BrushQuery(void)
	{
		ReleasePrivateData();
	}
	void ReleasePrivateData(void)
	{
		if (m_pReleaseFunc)
		{
			m_pReleaseFunc(this);
		}

		m_iCount = 0;
		m_pBrushes = NULL;
		m_iMaxBrushSides = 0;
		m_pReleaseFunc = NULL;
		m_pData = NULL;
	}

	inline int Count(void) const { return m_iCount; }
	inline uint32_t* Base(void) { return m_pBrushes; }
	inline uint32_t operator[](int iIndex) const { return m_pBrushes[iIndex]; }
	inline uint32_t GetBrushNumber(int iIndex) const { return m_pBrushes[iIndex]; }

	//maximum number of sides of any 1 brush in the query results
	inline int MaxBrushSides(void) const { return m_iMaxBrushSides; }

protected:
	int m_iCount;
	uint32_t* m_pBrushes;
	int m_iMaxBrushSides;
	void (*m_pReleaseFunc)(BrushQuery*); //release function is almost always in a different dll than calling code
	void* m_pData;
};

class EntityEnumerator
{
public:
	// This gets called with each handle
	virtual bool EnumEntity(HandleEntity* handleEntity) = 0;
};

struct AABB;
struct VirtualMeshList;
class PhysCollide;
class EngineTrace
{
public:
	// Returns the contents mask + entity at a particular world-space position
	virtual int		GetPointContents(const Vector& vecAbsPosition, int contentsMask = MASK_ALL, HandleEntity** ppEntity = NULL) = 0;

	// Returns the contents mask of the world only @ the world-space position (static props are ignored)
	virtual int		GetPointContents_WorldOnly(const Vector& vecAbsPosition, int contentsMask = MASK_ALL) = 0;

	// Get the point contents, but only test the specific entity. This works
	// on static props and brush models.
	//
	// If the entity isn't a static prop or a brush model, it returns CONTENTS_EMPTY and sets
	// bFailed to true if bFailed is non-null.
	virtual int		GetPointContents_Collideable(Collideable* pCollide, const Vector& vecAbsPosition) = 0;

	// Traces a ray against a particular entity
	virtual void	ClipRayToEntity(const Ray& ray, unsigned int fMask, HandleEntity* pEnt, Trace* pTrace) = 0;

	// Traces a ray against a particular entity
	virtual void	ClipRayToCollideable(const Ray& ray, unsigned int fMask, Collideable* pCollide, Trace* pTrace) = 0;

	// A version that simply accepts a ray (can work as a traceline or tracehull)
	virtual void	TraceRay(const Ray& ray, unsigned int fMask, TraceFilter* pTraceFilter, Trace* pTrace) = 0;

	// A version that sets up the leaf and entity lists and allows you to pass those in for collision.
	virtual void	SetupLeafAndEntityListRay(const Ray& ray, TraceListData* pTraceData) = 0;
	virtual void    SetupLeafAndEntityListBox(const Vector& vecBoxMin, const Vector& vecBoxMax, TraceListData* pTraceData) = 0;
	virtual void	TraceRayAgainstLeafAndEntityList(const Ray& ray, TraceListData* pTraceData, unsigned int fMask, TraceFilter* pTraceFilter, Trace* pTrace) = 0;

	// A version that sweeps a collideable through the world
	// abs start + abs end represents the collision origins you want to sweep the collideable through
	// vecAngles represents the collision angles of the collideable during the sweep
	virtual void	SweepCollideable(Collideable* pCollide, const Vector& vecAbsStart, const Vector& vecAbsEnd,
		const Vector& vecAngles, unsigned int fMask, TraceFilter* pTraceFilter, Trace* pTrace) = 0;

	// Enumerates over all entities along a ray
	// If triggers == true, it enumerates all triggers along a ray
	virtual void	EnumerateEntities(const Ray& ray, bool triggers, EntityEnumerator* pEnumerator) = 0;

	// Same thing, but enumerate entitys within a box
	virtual void	EnumerateEntities(const Vector& vecAbsMins, const Vector& vecAbsMaxs, EntityEnumerator* pEnumerator) = 0;

	// Convert a handle entity to a collideable.  Useful inside enumer
	virtual Collideable* GetCollideable(HandleEntity* pEntity) = 0;

	// HACKHACK: Temp for performance measurments
	virtual int GetStatByIndex(int index, bool bClear) = 0;


	//finds brushes in an AABB, prone to some false positives
	virtual void GetBrushesInAABB(const Vector& vMins, const Vector& vMaxs, BrushQuery& BrushQuery, int iContentsMask = 0xFFFFFFFF, int cmodelIndex = 0) = 0;

	//Creates a CPhysCollide out of all displacements wholly or partially contained in the specified AABB
	virtual PhysCollide* GetCollidableFromDisplacementsInAABB(const Vector& vMins, const Vector& vMaxs) = 0;

	// gets the number of displacements in the world
	virtual int GetNumDisplacements() = 0;

	// gets a specific diplacement mesh
	virtual void GetDisplacementMesh(int nIndex, VirtualMeshList* pMeshTriList) = 0;

	//retrieve brush planes and contents, returns zero if the brush doesn't exist,
	//returns positive number of sides filled out if the array can hold them all, negative number of slots needed to hold info if the array is too small
	virtual int GetBrushInfo(int iBrush, int& ContentsOut, BrushSideInfo* pBrushSideInfoOut, int iBrushSideInfoArraySize) = 0;

	virtual bool PointOutsideWorld(const Vector& ptTest) = 0; //Tests a point to see if it's outside any playable area

	// Walks bsp to find the leaf containing the specified point
	virtual int GetLeafContainingPoint(const Vector& ptTest) = 0;

	virtual TraceListData* AllocTraceListData() = 0;
	virtual void FreeTraceListData(TraceListData*) = 0;

	/// Used only in debugging: get/set/clear/increment the trace debug counter. See comment below for details.
	virtual int GetSetDebugTraceCounter(int value, DebugTraceCounterBehavior behavior) = 0;

	//Similar to GetCollidableFromDisplacementsInAABB(). But returns the intermediate mesh data instead of a collideable
	virtual int GetMeshesFromDisplacementsInAABB(const Vector& vMins, const Vector& vMaxs, VirtualMeshList* pOutputMeshes, int iMaxOutputMeshes) = 0;

	virtual void GetBrushesInCollideable(Collideable* pCollideable, BrushQuery& BrushQuery) = 0;

	virtual bool IsFullyOccluded(int nOcclusionKey, const AABB& aabb1, const AABB& aabb2, const Vector& vShadow) = 0;

	virtual void SuspendOcclusionTests() = 0;
	virtual void ResumeOcclusionTests() = 0;

	class AutoSuspendOcclusionTests
	{
		EngineTrace* engineTrace;
	public:
		AutoSuspendOcclusionTests(EngineTrace* engineTrace) : engineTrace(engineTrace) { engineTrace->SuspendOcclusionTests(); }
		~AutoSuspendOcclusionTests() { engineTrace->ResumeOcclusionTests(); }
	};

	virtual void FlushOcclusionQueries() = 0;
};
