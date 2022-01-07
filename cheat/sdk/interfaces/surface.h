#pragma once
#include "../definitions.h"

#include "appsystem.h"

#include "../data/vector.h"
#include "../data/matrix.h"

#define PRINTF_FORMAT_STRING _Printf_format_string_

enum FontFeature
{
	FONT_FEATURE_ANTIALIASED_FONTS = 1,
	FONT_FEATURE_DROPSHADOW_FONTS = 2,
	FONT_FEATURE_OUTLINE_FONTS = 6,
};

enum FontDrawType
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

enum FontFlags : int
{
	FONTFLAG_NONE = 0,
	FONTFLAG_ITALIC = (1 << 0),
	FONTFLAG_UNDERLINE = (1 << 1),
	FONTFLAG_STRIKEOUT = (1 << 2),
	FONTFLAG_SYMBOL = (1 << 3),
	FONTFLAG_ANTIALIAS = (1 << 4),
	FONTFLAG_GAUSSIANBLUR = (1 << 5),
	FONTFLAG_ROTARY = (1 << 6),
	FONTFLAG_DROPSHADOW = (1 << 7),
	FONTFLAG_ADDITIVE = (1 << 8),
	FONTFLAG_OUTLINE = (1 << 9),
	FONTFLAG_CUSTOM = (1 << 10),
	FONTFLAG_BITMAP = (1 << 11)
};

struct FontVertex
{
	FontVertex() {}
	FontVertex(const Vector2D& pos, const Vector2D& coord = Vector2D(0, 0))
	{
		m_Position = pos;
		m_TexCoord = coord;
	}
	void Init(const Vector2D& pos, const Vector2D& coord = Vector2D(0, 0))
	{
		m_Position = pos;
		m_TexCoord = coord;
	}

	Vector2D m_Position;
	Vector2D m_TexCoord;
};

using FontHandle = unsigned long;

struct FontCharRenderInfo
{
	// Text pos
	int				x, y;
	// Top left and bottom right
	// This is now a pointer to an array maintained by the surface, to avoid copying the data on the 360
	FontVertex* verts;
	int				textureId;
	int				abcA;
	int				abcB;
	int				abcC;
	int				fontTall;
	FontHandle	currentFont;
	// In:
	FontDrawType	drawType;
	wchar_t			ch;

	// Out
	bool			valid;
	// In/Out (true by default)
	bool			shouldclip;
};

struct IntRect
{
	int x0;
	int y0;
	int x1;
	int y1;
};

struct DrawTexturedRectParms
{
	int x0;
	int	y0;
	int x1;
	int y1;

	float s0;
	float t0;
	float s1;
	float t1;

	unsigned char alpha_ul;
	unsigned char alpha_ur;
	unsigned char alpha_lr;
	unsigned char alpha_ll;

	float angle;
};


struct Vertex
{
	Vertex() = default;
	Vertex(const Vector2D& pos, const Vector2D& coord = Vector2D(0, 0))
	{
		position = pos;
		coordinate = coord;
	}

	void Init(const Vector2D& pos, const Vector2D& coord = Vector2D(0, 0))
	{
		position = pos;
		coordinate = coord;
	}

	Vector2D position;
	Vector2D coordinate;
};

class HTML;
class HTMLEvents;
class Image;
enum ImageFormat;

class Surface : public AppSystem
{
public:
	void StartDrawing()
	{
		using StartDrawingFn = void(__thiscall*)(void*);
		static const auto StartDrawing = reinterpret_cast<StartDrawingFn>(m::sigs.startDrawing);
		StartDrawing(this);
	}

	void FinishDrawing()
	{
		using FinishDrawingFn = void(__thiscall*)(void*);
		static const auto FinishDrawing = reinterpret_cast<FinishDrawingFn>(m::sigs.finishDrawing);
		FinishDrawing(this);
	}

public:
	// call to Shutdown surface; surface can no longer be used after this is called
	virtual void Shutdown() override = 0;

	// frame
	virtual void RunFrame() = 0;

	// hierarchy root
	virtual VPANEL GetEmbeddedPanel() = 0;
	virtual void SetEmbeddedPanel(VPANEL pPanel) = 0;

	// drawing context
	virtual void PushMakeCurrent(VPANEL panel, bool useInsets) = 0;
	virtual void PopMakeCurrent(VPANEL panel) = 0;

	// rendering functions
	virtual void DrawSetColor(int r, int g, int b, int a = 255) = 0;
	virtual void DrawSetColor(Color col) = 0; // index 15

	virtual void DrawFilledRect(int x0, int y0, int x1, int y1) = 0;
	virtual void DrawFilledRectArray(IntRect* pRects, int numRects) = 0;
	virtual void DrawOutlinedRect(int x0, int y0, int x1, int y1) = 0;

	virtual void DrawLine(int x0, int y0, int x1, int y1) = 0; // 20
	virtual void DrawPolyLine(int* px, int* py, int numPoints) = 0;

	virtual void DrawSetApparentDepth(float depth) = 0;
	virtual void DrawClearApparentDepth() = 0;

	virtual void DrawSetTextFont(HFont font) = 0; // 24
	virtual void DrawSetTextColor(int r, int g, int b, int a) = 0;
	virtual void DrawSetTextColor(Color col) = 0;
	virtual void DrawSetTextPos(int x, int y) = 0;
	virtual void DrawGetTextPos(int& x, int& y) = 0;
	virtual void DrawPrintText(const wchar_t* text, int textLen, FontDrawType drawType = FONT_DRAW_DEFAULT) = 0;
	virtual void DrawUnicodeChar(wchar_t wch, FontDrawType drawType = FONT_DRAW_DEFAULT) = 0;

	virtual void DrawFlushText() = 0;		// flushes any buffered text (for rendering optimizations)
	virtual HTML* CreateHTMLWindow(HTMLEvents* events, VPANEL context) = 0;
	virtual void PaintHTMLWindow(HTML* htmlwin) = 0;
	virtual void DeleteHTMLWindow(HTML* htmlwin) = 0;

	enum TextureFormat
	{
		eTextureFormat_RGBA,
		eTextureFormat_BGRA,
		eTextureFormat_BGRA_Opaque, // bgra format but alpha is always 255, CEF does this, we can use this fact for better perf on win32 gdi
	};

	virtual int	 DrawGetTextureId(char const* filename) = 0;
	virtual bool DrawGetTextureFile(int id, char* filename, int maxlen) = 0;
	virtual void DrawSetTextureFile(int id, const char* filename, int hardwareFilter, bool forceReload) = 0;
	virtual void DrawSetTextureRGBA(int id, const unsigned char* rgba, int wide, int tall) = 0;
	virtual void DrawSetTexture(int id) = 0;
	virtual bool DeleteTextureByID(int id) = 0;

	virtual void DrawGetTextureSize(int id, int& wide, int& tall) = 0;
	virtual void DrawTexturedRect(int x0, int y0, int x1, int y1) = 0;
	virtual bool IsTextureIDValid(int id) = 0;

	virtual int CreateNewTextureID(bool procedural = false) = 0;

	virtual void GetScreenSize(int& wide, int& tall) = 0; // Index 44
	virtual void SetAsTopMost(VPANEL panel, bool state) = 0;
	virtual void BringToFront(VPANEL panel) = 0;
	virtual void SetForegroundWindow(VPANEL panel) = 0;
	virtual void SetPanelVisible(VPANEL panel, bool state) = 0;
	virtual void SetMinimized(VPANEL panel, bool state) = 0;
	virtual bool IsMinimized(VPANEL panel) = 0;
	virtual void FlashWindow(VPANEL panel, bool state) = 0;
	virtual void SetTitle(VPANEL panel, const wchar_t* title) = 0;
	virtual void SetAsToolBar(VPANEL panel, bool state) = 0;		// removes the window's task bar entry (for context menu's, etc.)

	// windows stuff
	virtual void CreatePopup(VPANEL panel, bool minimised, bool showTaskbarIcon = true, bool disabled = false, bool mouseInput = true, bool kbInput = true) = 0;
	virtual void SwapBuffers(VPANEL panel) = 0;
	virtual void Invalidate(VPANEL panel) = 0;
	virtual void SetCursor(HCursor cursor) = 0;
	virtual bool IsCursorVisible() = 0;
	virtual void ApplyChanges() = 0;
	virtual bool IsWithin(int x, int y) = 0;
	virtual bool HasFocus() = 0;

	// returns true if the surface supports minimize & maximize capabilities
	enum SurfaceFeature
	{
		ANTIALIASED_FONTS = FONT_FEATURE_ANTIALIASED_FONTS,
		DROPSHADOW_FONTS = FONT_FEATURE_DROPSHADOW_FONTS,
		ESCAPE_KEY = 3,
		OPENING_NEW_HTML_WINDOWS = 4,
		FRAME_MINIMIZE_MAXIMIZE = 5,
		OUTLINE_FONTS = FONT_FEATURE_OUTLINE_FONTS,
		DIRECT_HWND_RENDER = 7,
	};
	virtual bool SupportsFeature(SurfaceFeature feature) = 0;

	// restricts what gets drawn to one panel and it's children
	// currently only works in the game
	virtual void RestrictPaintToSinglePanel(VPANEL panel, bool bForceAllowNonModalSurface = false) = 0;

	// these two functions obselete, use IInput::SetAppModalSurface() instead
	virtual void SetModalPanel(VPANEL) = 0;
	virtual VPANEL GetModalPanel() = 0;

	virtual void UnlockCursor() = 0;
	virtual void LockCursor() = 0; // index 67
	virtual void SetTranslateExtendedKeys(bool state) = 0;
	virtual VPANEL GetTopmostPopup() = 0;

	// engine-only focus handling (replacing WM_FOCUS windows handling)
	virtual void SetTopLevelFocus(VPANEL panel) = 0;

	// fonts
	// creates an empty handle to a vgui font.  windows fonts can be add to this via SetFontGlyphSet().
	virtual HFont FontCreate() = 0; // Index 71

	virtual bool SetFontGlyphSet(HFont font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0) = 0;

	// adds a custom font file (only supports true type font files (.ttf) for now)
	virtual bool AddCustomFontFile(const char* fontFileName) = 0;

	// returns the details about the font
	virtual int GetFontTall(HFont font) = 0;
	virtual int GetFontAscent(HFont font, wchar_t wch) = 0;
	virtual bool IsFontAdditive(HFont font) = 0;
	virtual void GetCharABCwide(HFont font, int ch, int& a, int& b, int& c) = 0;
	virtual int GetCharacterWidth(HFont font, int ch) = 0;
	virtual void GetTextSize(HFont font, const wchar_t* text, int& wide, int& tall) = 0;

	// notify icons?!?
	virtual VPANEL GetNotifyPanel() = 0;
	virtual void SetNotifyIcon(VPANEL context, HTexture icon, VPANEL panelToReceiveMessages, const char* text) = 0;

	// plays a sound
	virtual void PlaySound(const char* fileName) = 0; // Index 82

	//!! these functions should not be accessed directly, but only through other vgui items
	//!! need to move these to seperate interface
	virtual int GetPopupCount() = 0;
	virtual VPANEL GetPopup(int index) = 0;
	virtual bool ShouldPaintChildPanel(VPANEL childPanel) = 0;
	virtual bool RecreateContext(VPANEL panel) = 0;
	virtual void AddPanel(VPANEL panel) = 0;
	virtual void ReleasePanel(VPANEL panel) = 0;
	virtual void MovePopupToFront(VPANEL panel) = 0;
	virtual void MovePopupToBack(VPANEL panel) = 0;

	virtual void SolveTraverse(VPANEL panel, bool forceApplySchemeSettings = false) = 0;
	virtual void PaintTraverse(VPANEL panel) = 0;

	virtual void EnableMouseCapture(VPANEL panel, bool state) = 0;

	// returns the size of the workspace
	virtual void GetWorkspaceBounds(int& x, int& y, int& wide, int& tall) = 0;

	// gets the absolute coordinates of the screen (in windows space)
	virtual void GetAbsoluteWindowBounds(int& x, int& y, int& wide, int& tall) = 0;

	// gets the base resolution used in proportional mode
	virtual void GetProportionalBase(int& width, int& height) = 0;

	virtual void CalculateMouseVisible() = 0;
	virtual bool NeedKBInput() = 0;

	virtual bool HasCursorPosFunctions() = 0;
	virtual void SurfaceGetCursorPos(int& x, int& y) = 0;
	virtual void SurfaceSetCursorPos(int x, int y) = 0;

	// SRC only functions!!!
	virtual void DrawTexturedLine(const Vertex& a, const Vertex& b) = 0;
	virtual void DrawOutlinedCircle(int x, int y, int radius, int segments) = 0;
	virtual void DrawTexturedPolyLine(const Vertex* p, int n) = 0; // (Note: this connects the first and last points).
	virtual void DrawTexturedSubRect(int x0, int y0, int x1, int y1, float texs0, float text0, float texs1, float text1) = 0;
	virtual void DrawTexturedPolygon(int n, Vertex* pVertice, bool bClipVertices = true) = 0;
	virtual const wchar_t* GetTitle(VPANEL panel) = 0;
	virtual bool IsCursorLocked(void) const = 0;
	virtual void SetWorkspaceInsets(int left, int top, int right, int bottom) = 0;

	// squarish comic book word bubble with pointer, rect params specify the space inside the bubble
	virtual void DrawWordBubble(int x0, int y0, int x1, int y1, int nBorderThickness, Color rgbaBackground, Color rgbaBorder,
		bool bPointer = false, int nPointerX = 0, int nPointerY = 0, int nPointerBaseThickness = 16) = 0;

	// Lower level char drawing code, call DrawGet then pass in info to DrawRender
	virtual bool DrawGetUnicodeCharRenderInfo(wchar_t ch, FontCharRenderInfo& info) = 0;
	virtual void DrawRenderCharFromInfo(const FontCharRenderInfo& info) = 0;

	// global alpha setting functions
	// affect all subsequent draw calls - shouldn't normally be used directly, only in Panel::PaintTraverse()
	virtual void DrawSetAlphaMultiplier(float alpha /* [0..1] */) = 0;
	virtual float DrawGetAlphaMultiplier() = 0;

	// web browser
	virtual void SetAllowHTMLJavaScript(bool state) = 0;

	// video mode changing
	virtual void OnScreenSizeChanged(int nOldWidth, int nOldHeight) = 0; // index 116

	virtual HCursor CreateCursorFromFile(char const* curOrAniFile, char const* pPathID = 0) = 0;

	// create IVguiMatInfo object ( IMaterial wrapper in VguiMatSurface, NULL in CWin32Surface )
	virtual void* DrawGetTextureMatInfoFactory(int id) = 0;

	virtual void PaintTraverseEx(VPANEL panel, bool paintPopups = false) = 0;

	virtual float GetZPos() const = 0;

	// From the Xbox
	virtual void SetPanelForInput(VPANEL vpanel) = 0;
	virtual void DrawFilledRectFastFade(int x0, int y0, int x1, int y1, int fadeStartPt, int fadeEndPt, unsigned int alpha0, unsigned int alpha1, bool bHorizontal) = 0;
	virtual void DrawFilledRectFade(int x0, int y0, int x1, int y1, unsigned int alpha0, unsigned int alpha1, bool bHorizontal) = 0;
	virtual void DrawSetTextureRGBAEx(int id, const unsigned char* rgba, int wide, int tall, ImageFormat imageFormat) = 0;
	virtual void DrawSetTextScale(float sx, float sy) = 0;
	virtual bool SetBitmapFontGlyphSet(HFont font, const char* windowsFontName, float scalex, float scaley, int flags) = 0;
	// adds a bitmap font file
	virtual bool AddBitmapFontFile(const char* fontFileName) = 0;
	// sets a symbol for the bitmap font
	virtual void SetBitmapFontName(const char* pName, const char* pFontFilename) = 0;
	// gets the bitmap font filename
	virtual const char* GetBitmapFontName(const char* pName) = 0;
	virtual void ClearTemporaryFontCache(void) = 0;

	virtual Image* GetIconImageForFullPath(char const* pFullPath) = 0;
	virtual void DrawUnicodeString(const wchar_t* pwString, FontDrawType drawType = FONT_DRAW_DEFAULT) = 0;
	virtual void PrecacheFontCharacters(HFont font, wchar_t* pCharacters) = 0;

	virtual const char* GetFontName(HFont font) = 0;

	virtual bool ForceScreenSizeOverride(bool bState, int wide, int tall) = 0;
	// LocalToScreen, ParentLocalToScreen fixups for explicit PaintTraverse calls on Panels not at 0, 0 position
	virtual bool ForceScreenPosOffset(bool bState, int x, int y) = 0;
	virtual void OffsetAbsPos(int& x, int& y) = 0;

	virtual void SetAbsPosForContext(int id, int x, int y) = 0;
	virtual void GetAbsPosForContext(int id, int& x, int& y) = 0;

	// Causes fonts to get reloaded, etc.
	virtual void ResetFontCaches() = 0;

	virtual bool IsScreenSizeOverrideActive(void) = 0;
	virtual bool IsScreenPosOverrideActive(void) = 0;

	virtual void DestroyTextureID(int id) = 0;

	virtual int GetTextureNumFrames(int id) = 0;
	virtual void DrawSetTextureFrame(int id, int nFrame, unsigned int* pFrameCache) = 0;

	virtual void GetClipRect(int& x0, int& y0, int& x1, int& y1) = 0;
	virtual void SetClipRect(int x0, int y0, int x1, int y1) = 0;

	virtual void DrawTexturedRectEx(DrawTexturedRectParms* pDrawParms) = 0;

	virtual void GetKernedCharWidth(HFont font, wchar_t ch, wchar_t chBefore, wchar_t chAfter, float& wide, float& abcA, float& abcC) = 0;

	virtual void DrawUpdateRegionTextureRGBA(int nTextureID, int x, int y, const unsigned char* pchData, int wide, int tall, ImageFormat imageFormat) = 0;
	virtual bool BHTMLWindowNeedsPaint(HTML* htmlwin) = 0;

	virtual void DrawSetTextureRGBALinear(int id, const unsigned char* rgba, int wide, int tall) = 0; // 152

	virtual const char* GetWebkitHTMLUserAgentString() = 0;

	virtual void* Deprecated_AccessChromeHTMLController() = 0; // 154

	// If the app drives the input (like the engine needs to do for VCR mode),
	// it can call this, setting bLetAppDriveInput to true and call
	// HandleInputEvent for the input events.
	virtual void SetAppDrivesInput(bool bLetAppDriveInput) = 0;

	// Tells the surface to ignore windows messages
	virtual void EnableWindowsMessages(bool bEnable) = 0;

	// Starts, ends 3D painting
	// NOTE: These methods should only be called from within the paint()
	// method of a panel.
	// When manual supersampling of rendertarget is enabled then the render
	// target will double the width and height of the rendering region if possible, or will otherwise
	// increase the rendering region to fill up the width/height of the render target maintaining
	// the aspect ratio.
	virtual void Begin3DPaint(int iLeft, int iTop, int iRight, int iBottom, bool bSupersampleRT = false) = 0;
	virtual void End3DPaint(bool bIgnoreAlphaWhenCompositing = false) = 0;

	// NOTE: This also should only be called from within the paint()
	// method of a panel. Use it to disable clipping for the rendering
	// of this panel.
	virtual void DisableClipping(bool bDisable) = 0;

	virtual void unknown0() = 0;
	virtual void unknown1() = 0;

	virtual void DrawColoredCircle(int centerx, int centery, float radius, int r, int g, int b, int a) = 0; // 162
	virtual void DrawColoredText(HFont font, int x, int y, int r, int g, int b, int a, PRINTF_FORMAT_STRING const char* fmt, ...) = 0;

	// Draws text with current font at position and wordwrapped to the rect using color values specified
	virtual void DrawColoredTextRect(HFont font, int x, int y, int w, int h, int r, int g, int b, int a, PRINTF_FORMAT_STRING const char* fmt, ...) = 0;
	virtual void DrawTextHeight(HFont font, int w, int& h, PRINTF_FORMAT_STRING char* fmt, ...) = 0;

	// Returns the length of the text string in pixels
	virtual int	DrawTextLen(HFont font, PRINTF_FORMAT_STRING const char* fmt, ...) = 0;

	// Draws a panel in 3D space. Assumes view + projection are already set up
	// Also assumes the (x,y) coordinates of the panels are defined in 640xN coords
	// (N isn't necessary 480 because the panel may not be 4x3)
	// The width + height specified are the size of the panel in world coordinates
	virtual void DrawPanelIn3DSpace(VPANEL pRootPanel, const ViewMatrix& panelCenterToWorld, int nPixelWidth, int nPixelHeight, float flWorldWidth, float flWorldHeight) = 0;

	// Binds a material to a surface texture ID
	virtual void DrawSetTextureMaterial(int id, Material* pMaterial) = 0;

	// Handles an input event, returns true if the event should be filtered from the rest of the game
	virtual bool HandleInputEvent(const InputEvent& event) = 0;

	virtual void Set3DPaintTempRenderTarget(const char* pRenderTargetName) = 0;
	virtual void Reset3DPaintTempRenderTarget(void) = 0;

	// Gets a material bound to a surface texture ID
	virtual Material* DrawGetTextureMaterial(int id) = 0;

	virtual void SetInputContext(InputContextHandle hContext) = 0;

	// uploads a part of a texture, used for font rendering
	virtual void DrawSetSubTextureRGBA(int textureID, int drawX, int drawY, unsigned const char* rgba, int subTextureWide, int subTextureTall) = 0;

	// Draws a gradient filled rect where the colors may be different
	virtual void DrawTexturedSubRectGradient(int x0, int y0, int x1, int y1, float texs0, float text0, float texs1, float text1, Color colStart, Color colEnd, bool bHorizontal) = 0;
};
