#include "../../include/minirt.h"

int	parse_camera(char **tokens, int count, t_scene *scene, char *err, size_t size)
{
	t_camera	camera;

	if (count != 4)
		return (set_error(err, size, "camera format: c <x,y,z> <nx,ny,nz> <fov>"), 0);
	if (!parse_vec3(tokens[1], &camera.position))
		return (set_error(err, size, "camera position is invalid"), 0);
	if (!parse_unit_vec(tokens[2], &camera.direction))
		return (set_error(err, size, "camera orientation must be a non-zero vector"), 0);
	if (!parse_double_strict(tokens[3], &camera.fov_degrees)
		|| camera.fov_degrees <= 0.0 || camera.fov_degrees > 180.0)
		return (set_error(err, size, "camera FOV must be in (0, 180]"), 0);
	camera.right = (t_vec){0.0, 0.0, 0.0};
	camera.up = (t_vec){0.0, 0.0, 0.0};
	camera.next = NULL;
	return (append_camera(scene, camera, err, size));
}
