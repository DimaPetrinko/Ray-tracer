#include "Texture.h"

Texture::Texture(const std::string& path) : bmp(path.c_str()) {}

Texture::Texture(const int& width, const int& height) : bmp(width, height) {}

Color Texture::GetPixel(const Vec2& uv) const
{
	uint8_t r, g, b, a;
	uint32_t x, y;

	x = uv.x * bmp.bmp_info_header.width;
	if (uv.x < 0) x = bmp.bmp_info_header.width + x;

	y = uv.y * bmp.bmp_info_header.height;
	if (uv.y < 0) y = bmp.bmp_info_header.height + y;

	bmp.get_pixel(x, y, b, g, r, a);
	return Color(r, g, b, a);
}

Color Texture::GetPixel(const int& u, const int& v) const
{
	uint8_t r, g, b, a;
	bmp.get_pixel(u, v, b, g, r, a);
	return Color(r, g, b, a);
}

void Texture::SetPixel(const Vec2& uv, const Color& color)
{
	uint32_t x, y;

	x = uv.x * bmp.bmp_info_header.width;
	if (uv.x < 0) x = bmp.bmp_info_header.width + x;

	y = uv.y * bmp.bmp_info_header.height;
	if (uv.y < 0) y = bmp.bmp_info_header.height + y;

	bmp.set_pixel(uv.x, uv.y, color.b(), color.g(), color.r(), color.a());
}

void Texture::SetPixel(const int& u, const int& v, const Color& color)
{
	bmp.set_pixel(u, v, color.b(), color.g(), color.r(), color.a());
}

void Texture::Save(const std::string& path)
{
	bmp.write(path.c_str());
}