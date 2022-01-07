#pragma once

// Little wrapper around surface calls
// NB: This has very specific use cases!

// e.g if you want to draw two lines which are
// the same color, using this class will call
// Surface::DrawSetColor twice, which is useless.
// In those cases you should rather manually call
// DSC once, and then make your two line draw calls
// through the Surface interface

class Color;
class Render
{
public:
	unsigned long tahoma = 0;

public:
	void Setup() noexcept;

	void Text(const char* text, const Color& color, int x, int y, unsigned long font) noexcept;
	void Text(const wchar_t* text, const Color& color, int x, int y, unsigned long font) noexcept;

	void Line(int x, int y, int x2, int y2, const Color& color);

	void Rect(int x, int y, int x2, int y2, const Color& color) noexcept;
	void RectFilled(int x, int y, int x2, int y2, const Color& color) noexcept;

	void Circle(int x, int y, int segments, int radius, const Color& color) noexcept;
};
