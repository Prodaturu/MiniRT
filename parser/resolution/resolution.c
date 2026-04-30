#include "../../include/minirt.h"

int	parse_resolution(char **tokens, int count, t_scene *scene, char *err, size_t size)
{
	if (count != 3)
		return (set_error(err, size, "resolution format: R <width> <height>"), 0);
	if (scene->has_resolution)
		return (set_error(err, size, "scene must contain exactly one resolution entry"), 0);
	if (!parse_int_strict(tokens[1], &scene->width)
		|| !parse_int_strict(tokens[2], &scene->height)
		|| scene->width <= 0 || scene->height <= 0)
		return (set_error(err, size, "resolution width and height must be positive"), 0);
	scene->has_resolution = true;
	return (1);
}
