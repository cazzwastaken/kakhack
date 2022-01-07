#pragma once
#include "../definitions.h"

#include "../data/matrix.h"

#define	TE_BEAMPOINTS			0	// beam effect between two points
#define TE_SPRITE				1	// additive sprite, plays 1 cycle
#define TE_BEAMDISK				2	// disk that expands to max radius over lifetime
#define TE_BEAMCYLINDER			3	// cylinder that expands to max radius over lifetime
#define TE_BEAMFOLLOW			4	// create a line of decaying beam segments until entity stops moving
#define TE_BEAMRING				5	// connect a beam ring to two entities
#define TE_BEAMSPLINE			6
#define TE_BEAMRINGPOINT		7
#define	TE_BEAMLASER			8	// fades according to viewpoint
#define TE_BEAMTESLA			9
#define MAX_BEAM_ENTS			10
#define NOISE_DIVISIONS			128

enum BeamType : unsigned int
{
	FBEAM_STARTENTITY = 0x00000001,
	FBEAM_ENDENTITY = 0x00000002,
	FBEAM_FADEIN = 0x00000004,
	FBEAM_FADEOUT = 0x00000008,
	FBEAM_SINENOISE = 0x00000010,
	FBEAM_SOLID = 0x00000020,
	FBEAM_SHADEIN = 0x00000040,
	FBEAM_SHADEOUT = 0x00000080,
	FBEAM_ONLYNOISEONCE = 0x00000100,	// only calculate our noise once
	FBEAM_NOTILE = 0x00000200,
	FBEAM_USE_HITBOXES = 0x00000400,	// attachment indices represent hitbox indices instead when this is set.
	FBEAM_STARTVISIBLE = 0x00000800,	// has this client actually seen this beam's start entity yet?
	FBEAM_ENDVISIBLE = 0x00001000,	// has this client actually seen this beam's end entity yet?
	FBEAM_ISACTIVE = 0x00002000,
	FBEAM_FOREVER = 0x00004000,
	FBEAM_HALOBEAM = 0x00008000,	// when drawing a beam with a halo, don't ignore the segments and endwidth
	FBEAM_REVERSED = 0x00010000,
};

struct BeamTrail
{
	BeamTrail* next;
	float die;
	Vector origin;
	Vector velocity;
};

struct Beam
{
	Beam() = default;

	// Methods of IClientRenderable
	virtual const Vector& GetRenderOrigin() = 0;
	virtual const Vector& GetRenderAngles() = 0;
	virtual const Matrix3x4& RenderableToWorldTransform() = 0;
	virtual void GetRenderBounds(Vector& mins, Vector& maxs) = 0;
	virtual bool ShouldDraw() = 0;
	virtual bool IsTransparent() = 0;
	virtual int DrawModel(int nFlags) = 0;
	virtual void ComputeFxBlend() = 0;
	virtual int GetFxBlend() = 0;

	Vector mins;
	Vector maxs;
	int* queryHandleHalo;
	float haloProxySize;
	Beam* next;
	int type;
	int flags;

	// Control points for the beam
	int				attachments;
	Vector			attachment[MAX_BEAM_ENTS];
	Vector			delta;

	// 0 .. 1 over lifetime of beam
	float			time;
	float			frequence;

	// Time when beam should die
	float			die;
	float			width;
	float			endWidth;
	float			fadeLength;
	float			amplitude;
	float			life;

	// Color
	float			r, g, b;
	float			brightness;

	// Speed
	float			speed;

	// Animation
	float			frameRate;
	float			frame;
	int				segments;

	// Attachment entities for the beam
	unsigned long entityHandle[MAX_BEAM_ENTS];
	int attachmentIndex[MAX_BEAM_ENTS];

	// Model info
	int				modelIndex;
	int				haloIndex;
	float			haloScale;
	int				frameCount;
	float			noise[NOISE_DIVISIONS + 1];

	// Popcorn trail for beam follows to use
	BeamTrail* trail;

	// for TE_BEAMRINGPOINT
	float			startRadius;
	float			endRadius;

	// for FBEAM_ONLYNOISEONCE
	bool			calculatedNoise;
	float			HDRColorScale;
};

class BaseEntity;
struct BeamInfo
{
	BeamInfo()
	{
		type = TE_BEAMRINGPOINT;
		segments = -1;
		modelName = nullptr;
		haloName = nullptr;
		modelIndex = -1;
		haloIndex = -1;
		renderable = true;
		flags = 0;
	}

	constexpr void SetColor(const std::array<float, 4U>& colors)
	{
		red = colors[0] * 255.f;
		green = colors[1] * 255.f;
		blue = colors[2] * 255.f;
		brightness = colors[3] * 255.f;
	}

	int				type;

	// Entities
	BaseEntity* startEntity;
	int				startAttachment;
	BaseEntity* endEntity;
	int				endAttachment;

	// Points
	Vector			start;
	Vector			end;

	int				modelIndex;
	const char* modelName;
	int				haloIndex;
	const char* haloName;
	float			haloScale;
	float			life;
	float			width;
	float			endWidth;
	float			fadeLength;
	float			amplitude;
	float			brightness;
	float			speed;
	int				startFrame;
	float			frameRate;
	float			red;
	float			green;
	float			blue;
	bool			renderable;
	int				segments;
	int				flags;

	// Rings
	Vector			center;
	float			startRadius;
	float			endRadius;
};

class CBeam;
class ViewRenderBeams
{
public:
	virtual				~ViewRenderBeams(void) = 0;

	// Implement IViewRenderBeams
	virtual	void		InitBeams(void) = 0;
	virtual	void		ShutdownBeams(void) = 0;
	virtual	void		ClearBeams(void) = 0;

	// Updates the state of the temp ent beams
	virtual void		UpdateTempEntBeams() = 0;

	virtual void		DrawBeam(Beam* pbeam) = 0;
	virtual void		DrawBeam(CBeam* pbeam, TraceFilter* entityBeamTraceFilter = NULL) = 0;

	virtual	void		KillDeadBeams(ClientEntity* pDeadEntity) = 0;

	virtual	void		CreateBeamEnts(int startEnt, int endEnt, int modelIndex, int haloIndex, float haloScale,
		float life, float width, float endWidth, float fadeLength, float amplitude,
		float brightness, float speed, int startFrame,
		float framerate, float r, float g, float b, int type = -1) = 0;
	virtual Beam* CreateBeamEnts(BeamInfo& beamInfo) = 0;

	virtual	void		CreateBeamEntPoint(int	nStartEntity, const Vector* pStart, int nEndEntity, const Vector* pEnd,
		int modelIndex, int haloIndex, float haloScale,
		float life, float width, float endWidth, float fadeLength, float amplitude,
		float brightness, float speed, int startFrame,
		float framerate, float r, float g, float b) = 0;
	virtual Beam* CreateBeamEntPoint(BeamInfo& beamInfo) = 0;

	virtual	void		CreateBeamPoints(Vector& start, Vector& end, int modelIndex, int haloIndex, float haloScale,
		float life, float width, float endWidth, float fadeLength, float amplitude,
		float brightness, float speed, int startFrame,
		float framerate, float r, float g, float b) = 0;
	virtual	Beam* CreateBeamPoints(BeamInfo& beamInfo) = 0;

	virtual	void		CreateBeamRing(int startEnt, int endEnt, int modelIndex, int haloIndex, float haloScale,
		float life, float width, float endWidth, float fadeLength, float amplitude,
		float brightness, float speed, int startFrame,
		float framerate, float r, float g, float b, int flags) = 0;
	virtual Beam* CreateBeamRing(BeamInfo& beamInfo) = 0;

	virtual void		CreateBeamRingPoint(const Vector& center, float start_radius, float end_radius, int modelIndex, int haloIndex, float haloScale,
		float life, float width, float m_nEndWidth, float m_nFadeLength, float amplitude,
		float brightness, float speed, int startFrame,
		float framerate, float r, float g, float b, int flags) = 0;
	virtual Beam* CreateBeamRingPoint(BeamInfo& beamInfo) = 0;

	virtual	void		CreateBeamCirclePoints(int type, Vector& start, Vector& end,
		int modelIndex, int haloIndex, float haloScale, float life, float width,
		float endWidth, float fadeLength, float amplitude, float brightness, float speed,
		int startFrame, float framerate, float r, float g, float b) = 0;
	virtual Beam* CreateBeamCirclePoints(BeamInfo& beamInfo) = 0;

	virtual	void		CreateBeamFollow(int startEnt, int modelIndex, int haloIndex, float haloScale,
		float life, float width, float endWidth, float fadeLength, float r, float g, float b,
		float brightness) = 0;
	virtual Beam* CreateBeamFollow(BeamInfo& beamInfo) = 0;
};
