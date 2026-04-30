#include "../include/minirt.h"

int	append_camera(t_scene *scene, t_camera camera, char *err, size_t size)
{
	t_camera	*node;
	t_camera	*tail;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (set_error(err, size, "memory allocation failed while adding a camera"), 0);
	*node = camera;
	node->next = NULL;
	if (scene->cameras == NULL)
		scene->cameras = node;
	else
	{
		tail = scene->cameras;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = node;
	}
	scene->camera_count++;
	if (scene->active_camera == NULL)
		scene->active_camera = node;
	return (1);
}

int	append_light(t_scene *scene, t_light light, char *err, size_t size)
{
	t_light	*node;
	t_light	*tail;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (set_error(err, size, "memory allocation failed while adding a light"), 0);
	*node = light;
	node->next = NULL;
	if (scene->lights == NULL)
		scene->lights = node;
	else
	{
		tail = scene->lights;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = node;
	}
	scene->light_count++;
	return (1);
}

int	append_object(t_scene *scene, t_object object, char *err, size_t size)
{
	t_object	*node;
	t_object	*tail;

	node = malloc(sizeof(*node));
	if (node == NULL)
		return (set_error(err, size, "memory allocation failed while adding an object"), 0);
	*node = object;
	node->next = NULL;
	if (scene->objects == NULL)
		scene->objects = node;
	else
	{
		tail = scene->objects;
		while (tail->next != NULL)
			tail = tail->next;
		tail->next = node;
	}
	scene->object_count++;
	return (1);
}

void	scene_free(t_scene *scene)
{
	t_camera	*camera;
	t_camera	*next_camera;
	t_light		*light;
	t_light		*next_light;
	t_object	*current;
	t_object	*next;

	camera = scene->cameras;
	while (camera != NULL)
	{
		next_camera = camera->next;
		free(camera);
		camera = next_camera;
	}
	light = scene->lights;
	while (light != NULL)
	{
		next_light = light->next;
		free(light);
		light = next_light;
	}
	current = scene->objects;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	scene->cameras = NULL;
	scene->lights = NULL;
	scene->active_camera = NULL;
	scene->objects = NULL;
	scene->camera_count = 0;
	scene->light_count = 0;
	scene->object_count = 0;
}
