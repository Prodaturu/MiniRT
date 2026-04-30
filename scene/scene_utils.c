#include "../include/minirt.h"

t_color	color_add(t_color a, t_color b)
{
	return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b});
}

t_color	color_scale(t_color color, double scale)
{
	return ((t_color){color.r * scale, color.g * scale, color.b * scale});
}

t_color	color_mul(t_color a, t_color b)
{
	return ((t_color){a.r * b.r, a.g * b.g, a.b * b.b});
}

t_color	color_clamp(t_color color)
{
	if (color.r < 0.0)
		color.r = 0.0;
	if (color.g < 0.0)
		color.g = 0.0;
	if (color.b < 0.0)
		color.b = 0.0;
	if (color.r > 1.0)
		color.r = 1.0;
	if (color.g > 1.0)
		color.g = 1.0;
	if (color.b > 1.0)
		color.b = 1.0;
	return (color);
}

uint32_t	rgba_from_color(t_color color)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	color = color_clamp(color);
	r = (uint32_t)lrint(color.r * 255.0);
	g = (uint32_t)lrint(color.g * 255.0);
	b = (uint32_t)lrint(color.b * 255.0);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFFu);
}
