#include "../include/minirt.h"

static void	blit_framebuffer(t_main_rt *rt)
{
	int			x;
	int			y;
	int			src_x;
	int			src_y;
	uint32_t	color;

	y = 0;
	while (y < rt->scene.window_height)
	{
		x = 0;
		while (x < rt->scene.window_width)
		{
			src_x = (int)((double)x * (double)rt->scene.width
					/ (double)rt->scene.window_width);
			src_y = (int)((double)y * (double)rt->scene.height
					/ (double)rt->scene.window_height);
			color = rt->framebuffer[(size_t)src_y * (size_t)rt->scene.width + (size_t)src_x];
			mlx_put_pixel(rt->img, x, y, color);
			x++;
		}
		y++;
	}
}

static void	switch_camera(t_main_rt *rt, int direction)
{
	t_camera	*camera;
	t_camera	*previous;

	if (rt->scene.camera_count < 2)
		return ;
	if (direction > 0)
	{
		rt->scene.active_camera = rt->scene.active_camera->next;
		if (rt->scene.active_camera == NULL)
			rt->scene.active_camera = rt->scene.cameras;
	}
	else
	{
		camera = rt->scene.cameras;
		previous = camera;
		while (camera != rt->scene.active_camera)
		{
			previous = camera;
			camera = camera->next;
		}
		if (camera == rt->scene.cameras)
		{
			while (previous->next != NULL)
				previous = previous->next;
			rt->scene.active_camera = previous;
		}
		else
			rt->scene.active_camera = previous;
	}
	scene_render(rt);
	blit_framebuffer(rt);
}

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_main_rt	*rt;

	rt = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(rt->mlx);
	else if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
		&& keydata.action == MLX_PRESS)
		switch_camera(rt, 1);
	else if ((keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
		&& keydata.action == MLX_PRESS)
		switch_camera(rt, -1);
}

int	renderer(t_main_rt *rt, char *err, size_t size)
{
	int32_t	monitor_width;
	int32_t	monitor_height;

	monitor_width = rt->scene.width;
	monitor_height = rt->scene.height;
	mlx_get_monitor_size(0, &monitor_width, &monitor_height);
	if (monitor_width > 0 && monitor_height > 0)
	{
		if (rt->scene.window_width > monitor_width)
			rt->scene.window_width = monitor_width;
		if (rt->scene.window_height > monitor_height)
			rt->scene.window_height = monitor_height;
	}
	rt->mlx = mlx_init(rt->scene.window_width, rt->scene.window_height, "miniRT", true);
	if (rt->mlx == NULL)
		return (set_error(err, size, "failed to initialize MLX"), 0);
	rt->img = mlx_new_image(rt->mlx, rt->scene.window_width, rt->scene.window_height);
	if (rt->img == NULL || mlx_image_to_window(rt->mlx, rt->img, 0, 0) < 0)
	{
		mlx_terminate(rt->mlx);
		rt->mlx = NULL;
		return (set_error(err, size, "failed to create render image"), 0);
	}
	scene_render(rt);
	if (rt->framebuffer == NULL)
	{
		mlx_terminate(rt->mlx);
		rt->mlx = NULL;
		return (set_error(err, size, "failed to allocate framebuffer"), 0);
	}
	blit_framebuffer(rt);
	mlx_key_hook(rt->mlx, key_hook, rt);
	mlx_loop(rt->mlx);
	mlx_terminate(rt->mlx);
	rt->mlx = NULL;
	rt->img = NULL;
	return (1);
}
