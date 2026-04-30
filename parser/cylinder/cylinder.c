#include "../../include/minirt.h"

int	parse_cylinder(char **tokens, int count, t_scene *scene, char *err, size_t size)
{
	t_object	object;
	double		diameter;
	double		height;

	if (count != 6)
		return (set_error(err, size, "cylinder format: cy <x,y,z> <nx,ny,nz> <diameter> <height> <R,G,B>"), 0);
	if (!parse_vec3(tokens[1], &object.position))
		return (set_error(err, size, "cylinder center is invalid"), 0);
	if (!parse_unit_vec(tokens[2], &object.direction))
		return (set_error(err, size, "cylinder axis must be a non-zero vector"), 0);
	if (!parse_double_strict(tokens[3], &diameter) || diameter <= 0.0)
		return (set_error(err, size, "cylinder diameter must be > 0"), 0);
	if (!parse_double_strict(tokens[4], &height) || height <= 0.0)
		return (set_error(err, size, "cylinder height must be > 0"), 0);
	if (!parse_color_rgb(tokens[5], &object.color))
		return (set_error(err, size, "cylinder color must use RGB values in [0,255]"), 0);
	object.type = OBJ_CYLINDER;
	object.radius = diameter * 0.5;
	object.height = height;
	object.size = 0.0;
	object.vertex_b = (t_vec){0.0, 0.0, 0.0};
	object.vertex_c = (t_vec){0.0, 0.0, 0.0};
	object.next = NULL;
	return (append_object(scene, object, err, size));
}
