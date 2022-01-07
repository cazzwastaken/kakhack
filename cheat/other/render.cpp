#include "render.h"

#include "../core/interfaces.h"
#include <Windows.h>

void Render::Setup() noexcept
{
	// Setup fonts
	tahoma = i::surface->FontCreate();
	i::surface->SetFontGlyphSet(tahoma, "tahoma", 14, 500, 0, 0, FONTFLAG_DROPSHADOW);

	// probably should check for failure lol
}

void Render::Text(const char* text, const Color& color, int x, int y, unsigned long font) noexcept
{
	wchar_t buffer[128];

	if (MultiByteToWideChar(CP_UTF8, 0,text, -1, buffer, 128) < 0)
		return;

	i::surface->DrawSetTextColor(color);
	i::surface->DrawSetTextFont(font);
	i::surface->DrawSetTextPos(x, y);

	i::surface->DrawPrintText(buffer, wcslen(buffer));
}

void Render::Text(const wchar_t* text, const Color& color, int x, int y, unsigned long font) noexcept
{
	i::surface->DrawSetTextColor(color);
	i::surface->DrawSetTextFont(font);
	i::surface->DrawSetTextPos(x, y);

	i::surface->DrawPrintText(text, wcslen(text));
}

void Render::Line(int x, int y, int x2, int y2, const Color& color)
{
	i::surface->DrawSetColor(color);
	i::surface->DrawLine(x, y, x2, y2);
}

void Render::Rect(int x, int y, int x2, int y2, const Color& color) noexcept
{
	i::surface->DrawSetColor(color);
	i::surface->DrawOutlinedRect(x, y, x2, y2);
}

void Render::RectFilled(int x, int y, int x2, int y2, const Color& color) noexcept
{
	i::surface->DrawSetColor(color);
	i::surface->DrawFilledRect(x, y, x2, y2);
}

void Render::Circle(int x, int y, int radius, int segments, const Color& color) noexcept
{
	i::surface->DrawSetColor(color);
	i::surface->DrawOutlinedCircle(x, y, radius, segments);
}
