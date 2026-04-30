#include "../../include/minirt.h"

int	parse_sphere(char **tokens, int count, t_scene *scene, char *err, size_t size)
{
	t_object	object;
	double		diameter;

	if (count != 4)
		return (set_error(err, size, "sphere format: sp <x,y,z> <diameter> <R,G,B>"), 0);
	if (!parse_vec3(tokens[1], &object.position))
		return (set_error(err, size, "sphere center is invalid"), 0);
	if (!parse_double_strict(tokens[2], &diameter) || diameter <= 0.0)
		return (set_error(err, size, "sphere diameter must be > 0"), 0);
	if (!parse_color_rgb(tokens[3], &object.color))
		return (set_error(err, size, "sphere color must use RGB values in [0,255]"), 0);
	memset(&object.direction, 0, sizeof(object.direction));
	object.type = OBJ_SPHERE;
	object.radius = diameter * 0.5;
	object.height = 0.0;
	object.size = 0.0;
	object.vertex_b = (t_vec){0.0, 0.0, 0.0};
	object.vertex_c = (t_vec){0.0, 0.0, 0.0};
	object.next = NULL;
	return (append_object(scene, object, err, size));
}
