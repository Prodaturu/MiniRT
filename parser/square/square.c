#include "../../include/minirt.h"

int	parse_square(char **tokens, int count, t_scene *scene, char *err, size_t size)
{
	t_object	object;

	if (count != 5)
		return (set_error(err, size, "square format: sq <x,y,z> <nx,ny,nz> <size> <R,G,B>"), 0);
	if (!parse_vec3(tokens[1], &object.position))
		return (set_error(err, size, "square center is invalid"), 0);
	if (!parse_unit_vec(tokens[2], &object.direction))
		return (set_error(err, size, "square normal must be a non-zero vector"), 0);
	if (!parse_double_strict(tokens[3], &object.size) || object.size <= 0.0)
		return (set_error(err, size, "square size must be > 0"), 0);
	if (!parse_color_rgb(tokens[4], &object.color))
		return (set_error(err, size, "square color must use RGB values in [0,255]"), 0);
	object.type = OBJ_SQUARE;
	object.radius = 0.0;
	object.height = 0.0;
	object.vertex_b = (t_vec){0.0, 0.0, 0.0};
	object.vertex_c = (t_vec){0.0, 0.0, 0.0};
	object.next = NULL;
	return (append_object(scene, object, err, size));
}
