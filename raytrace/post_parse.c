#include "../include/minirt.h"

t_ray	make_camera_ray(const t_scene *scene, int x, int y)
{
	double	aspect;
	double	scale;
	double	px;
	double	py;
	t_vec	dir;
	t_camera	*camera;

	camera = scene->active_camera;
	aspect = (double)scene->width / (double)scene->height;
	scale = tan((camera->fov_degrees * M_PI / 180.0) * 0.5);
	px = (2.0 * (((double)x + 0.5) / (double)scene->width) - 1.0) * aspect * scale;
	py = (1.0 - 2.0 * (((double)y + 0.5) / (double)scene->height)) * scale;
	dir = vec_add(camera->direction,
			vec_add(vec_scale(camera->right, px),
				vec_scale(camera->up, py)));
	return ((t_ray){camera->position, vec_normalize(dir)});
}

void	set_framebuffer_pixel(t_main_rt *rt, int x, int y, uint32_t color)
{
	rt->framebuffer[(size_t)y * (size_t)rt->scene.width + (size_t)x] = color;
}

void	scene_render(t_main_rt *rt)
{
	int		x;
	int		y;
	t_ray	ray;
	uint32_t	color;

	if (rt->framebuffer == NULL)
		rt->framebuffer = malloc(sizeof(uint32_t) * (size_t)rt->scene.width
				* (size_t)rt->scene.height);
	if (rt->framebuffer == NULL)
		return ;
	y = 0;
	while (y < rt->scene.height)
	{
		x = 0;
		while (x < rt->scene.width)
		{
			ray = make_camera_ray(&rt->scene, x, y);
			color = rgba_from_color(trace_ray(&rt->scene, ray));
			set_framebuffer_pixel(rt, x, y, color);
			x++;
		}
		y++;
	}
}
