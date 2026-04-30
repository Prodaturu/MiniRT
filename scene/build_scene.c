#include "../include/minirt.h"

int	init_scene_struct(t_scene *scene, char *err, size_t size)
{
	t_camera	*camera;
	t_vec	world_up;

	if (!scene->has_resolution)
		return (set_error(err, size, "scene must contain one resolution entry"), 0);
	if (!scene->has_ambient)
		return (set_error(err, size, "scene must contain one ambient light"), 0);
	if (scene->cameras == NULL)
		return (set_error(err, size, "scene must contain at least one camera"), 0);
	if (scene->lights == NULL)
		return (set_error(err, size, "scene must contain at least one light"), 0);
	if (scene->objects == NULL)
		return (set_error(err, size, "scene must contain at least one object"), 0);
	camera = scene->cameras;
	while (camera != NULL)
	{
		world_up = (t_vec){0.0, 1.0, 0.0};
		if (fabs(vec_dot(camera->direction, world_up)) > 0.999)
			world_up = (t_vec){0.0, 0.0, 1.0};
		camera->right = vec_normalize(vec_cross(camera->direction, world_up));
		camera->up = vec_normalize(vec_cross(camera->right, camera->direction));
		camera = camera->next;
	}
	scene->window_width = scene->width;
	scene->window_height = scene->height;
	return (1);
}
