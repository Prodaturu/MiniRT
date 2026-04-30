#include "../../include/minirt.h"

int	parse_ambient(char **tokens, int count, t_scene *scene, char *err, size_t size)
{
	if (count != 3)
		return (set_error(err, size, "ambient format: A <ratio> <R,G,B>"), 0);
	if (scene->has_ambient)
		return (set_error(err, size, "scene must contain exactly one ambient light"), 0);
	if (!parse_double_strict(tokens[1], &scene->ambient.ratio)
		|| scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		return (set_error(err, size, "ambient ratio must be in [0.0, 1.0]"), 0);
	if (!parse_color_rgb(tokens[2], &scene->ambient.color))
		return (set_error(err, size, "ambient color must use RGB values in [0,255]"), 0);
	scene->has_ambient = true;
	return (1);
}
