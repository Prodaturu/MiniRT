#include "../../include/minirt.h"

int	parse_triangle(char **tokens, int count, t_scene *scene, char *err, size_t size)
{
	t_object	object;
	t_vec		edge1;
	t_vec		edge2;

	if (count != 5)
		return (set_error(err, size, "triangle format: tr <p1> <p2> <p3> <R,G,B>"), 0);
	if (!parse_vec3(tokens[1], &object.position)
		|| !parse_vec3(tokens[2], &object.vertex_b)
		|| !parse_vec3(tokens[3], &object.vertex_c))
		return (set_error(err, size, "triangle vertices are invalid"), 0);
	if (!parse_color_rgb(tokens[4], &object.color))
		return (set_error(err, size, "triangle color must use RGB values in [0,255]"), 0);
	edge1 = vec_sub(object.vertex_b, object.position);
	edge2 = vec_sub(object.vertex_c, object.position);
	object.direction = vec_normalize(vec_cross(edge1, edge2));
	if (vec_length(object.direction) < EPSILON)
		return (set_error(err, size, "triangle vertices must not be collinear"), 0);
	object.type = OBJ_TRIANGLE;
	object.radius = 0.0;
	object.height = 0.0;
	object.size = 0.0;
	object.next = NULL;
	return (append_object(scene, object, err, size));
}
