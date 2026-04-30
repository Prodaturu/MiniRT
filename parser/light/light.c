#include "../../include/minirt.h"

int	parse_light(char **tokens, int count, t_scene *scene, char *err, size_t size)
{
	t_light	light;

	if (count != 3 && count != 4)
		return (set_error(err, size, "light format: l <x,y,z> <ratio> [R,G,B]"), 0);
	if (!parse_vec3(tokens[1], &light.position))
		return (set_error(err, size, "light position is invalid"), 0);
	if (!parse_double_strict(tokens[2], &light.ratio)
		|| light.ratio < 0.0 || light.ratio > 1.0)
		return (set_error(err, size, "light ratio must be in [0.0, 1.0]"), 0);
	light.color = (t_color){1.0, 1.0, 1.0};
	if (count == 4 && !parse_color_rgb(tokens[3], &light.color))
		return (set_error(err, size, "light color must use RGB values in [0,255]"), 0);
	light.next = NULL;
	return (append_light(scene, light, err, size));
}
