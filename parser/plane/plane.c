#include "../../include/minirt.h"

int	parse_plane(char **tokens, int count, t_scene *scene, char *err, size_t size)
{
	t_object	object;

	if (count != 4)
		return (set_error(err, size, "plane format: pl <x,y,z> <nx,ny,nz> <R,G,B>"), 0);
	if (!parse_vec3(tokens[1], &object.position))
		return (set_error(err, size, "plane point is invalid"), 0);
	if (!parse_unit_vec(tokens[2], &object.direction))
		return (set_error(err, size, "plane normal must be a non-zero vector"), 0);
	if (!parse_color_rgb(tokens[3], &object.color))
		return (set_error(err, size, "plane color must use RGB values in [0,255]"), 0);
	object.type = OBJ_PLANE;
	object.radius = 0.0;
	object.height = 0.0;
	object.size = 0.0;
	object.vertex_b = (t_vec){0.0, 0.0, 0.0};
	object.vertex_c = (t_vec){0.0, 0.0, 0.0};
	object.next = NULL;
	return (append_object(scene, object, err, size));
}
