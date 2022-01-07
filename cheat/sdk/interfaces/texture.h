#pragma once
#include "../definitions.h"

class VTFTexture;
class Texture;

enum MaterialRenderTargetDepth
{
	MATERIAL_RT_DEPTH_SHARED = 0x0,
	MATERIAL_RT_DEPTH_SEPARATE = 0x1,
	MATERIAL_RT_DEPTH_NONE = 0x2,
	MATERIAL_RT_DEPTH_ONLY = 0x3,
};

struct AsyncTextureContext
{
	Texture* texture;

	// snapshot at the point of async start
	// used to resolve disparity at moment of latent async arrival
	unsigned int	internalFlags;
	int				desiredTempDimensionLimit;
	int				actualDimensionLimit;

	// Keeps track of the VTF texture in case the shader api texture gets
	// created the next frame. Generating the texture from the file can
	// then be split in multiple parts across frames.
	VTFTexture* m_pVTFTexture;
};

class TextureRegenerator
{
public:
	// This will be called when the texture bits need to be regenerated.
	// Use the VTFTexture interface, which has been set up with the
	// appropriate texture size + format
	// The rect specifies which part of the texture needs to be updated
	// You can choose to update all of the bits if you prefer
	virtual void RegenerateTextureBits(Texture * pTexture, VTFTexture * pVTFTexture, Rect * pRect) = 0;

	// This will be called when the regenerator needs to be deleted
	// which will happen when the texture is destroyed
	virtual void Release() = 0;

	virtual bool HasPreallocatedScratchTexture() const { return false; }
	virtual VTFTexture* GetPreallocatedScratchTexture() { return 0; }
};

class Texture
{
public:
	// Various texture polling methods
	virtual const char* GetName(void) const = 0;
	virtual int GetMappingWidth() const = 0;
	virtual int GetMappingHeight() const = 0;
	virtual int GetActualWidth() const = 0;
	virtual int GetActualHeight() const = 0;
	virtual int GetNumAnimationFrames() const = 0;
	virtual bool IsTranslucent() const = 0;
	virtual bool IsMipmapped() const = 0;

	virtual void GetLowResColorSample(float s, float t, float* color) const = 0;

	// Gets texture resource data of the specified type.
	// Params:
	//		eDataType		type of resource to retrieve.
	//		pnumBytes		on return is the number of bytes available in the read-only data buffer or is undefined
	// Returns:
	//		pointer to the resource data, or NULL
	virtual void* GetResourceData(uint32_t eDataType, size_t* pNumBytes) const = 0;

	// Methods associated with reference count
	virtual void IncrementReferenceCount(void) = 0;
	virtual void DecrementReferenceCount(void) = 0;

	inline void AddRef() { IncrementReferenceCount(); }
	inline void Release() { DecrementReferenceCount(); }

	// Used to modify the texture bits (procedural textures only)
	virtual void SetTextureRegenerator(TextureRegenerator* pTextureRegen, bool releaseExisting = true) = 0;

	// Reconstruct the texture bits in HW memory

	// If rect is not specified, reconstruct all bits, otherwise just
	// reconstruct a subrect.
	virtual void Download(Rect* pRect = 0, int nAdditionalCreationFlags = 0) = 0;

	// Uses for stats. . .get the approximate size of the texture in it's current format.
	virtual int GetApproximateVidMemBytes(void) const = 0;

	// Returns true if the texture data couldn't be loaded.
	virtual bool IsError() const = 0;

	// NOTE: Stuff after this is added after shipping HL2.

	// For volume textures
	virtual bool IsVolumeTexture() const = 0;
	virtual int GetMappingDepth() const = 0;
	virtual int GetActualDepth() const = 0;

	virtual ImageFormat GetImageFormat() const = 0;

	// Various information about the texture
	virtual bool IsRenderTarget() const = 0;
	virtual bool IsCubeMap() const = 0;
	virtual bool IsNormalMap() const = 0;
	virtual bool IsProcedural() const = 0;
	virtual bool IsDefaultPool() const = 0;

	virtual void DeleteIfUnreferenced() = 0;

	// swap everything except the name with another texture
	virtual void SwapContents(Texture* pOther) = 0;

	// Retrieve the vtf flags mask
	virtual unsigned int GetFlags(void) const = 0;

	// Force LOD override (automatically downloads the texture)
	virtual void ForceLODOverride(int iNumLodsOverrideUpOrDown) = 0;

	// Force exclude override (automatically downloads the texture)
	virtual void ForceExcludeOverride(int iExcludeOverride) = 0;

	//swap out the active texture surface, only valid for MultiRenderTarget textures
	virtual void AddDownsizedSubTarget(const char* szName, int iDownsizePow2, MaterialRenderTargetDepth depth) = 0;
	virtual void SetActiveSubTarget(const char* szName) = 0; //NULL to return to base target

	virtual int GetReferenceCount() const = 0;

	virtual bool IsTempExcluded() const = 0;
	virtual bool CanBeTempExcluded() const = 0;

	virtual bool FinishAsyncDownload(AsyncTextureContext* pContext, void* pData, int nNumReadBytes, bool bAbort, float flMaxTimeMs) = 0;

	virtual bool IsForceExcluded() const = 0;
	virtual bool ClearForceExclusion() = 0;
};
