/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 22:21:20 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/22 03:12:51 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	scene_render(t_main_rt *main_rt);
t_ray	*get_ray(t_scene *scene, double x, double y);

void	scene_render(t_main_rt *main_rt)
{
	t_scene		*scene;
	t_ray		*ray;
	t_color		*color;
	int			x;
	int			y;

	x = 0;
	y = 0;
	scene = main_rt->scene;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			printf("DEBUG!!\n");
			ray = get_ray(scene, x, y);
			color = ray_color(ray, scene, main_rt->parser->light);
			// set_pixel(x, y, color);
			mlx_put_pixel(main_rt->img, x, y, ray->col);
			x++;
		}
		y++;
	}
}

t_ray	*get_ray(t_scene *scene, double x, double y)
{
	t_ray		*ray;
	t_garbage	*gc;
	t_vector	*origin;
	t_vector	*dir;
	double		aspect_ratio;

	ray = malloc(sizeof(t_ray));
	ray->origin = malloc(sizeof(t_vector));
	ray->direction = malloc(sizeof(t_vector));
	gc = scene->garbage_col;
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	x = (2 * x / (double)WIDTH - 1) * aspect_ratio;
	y = (1 - 2 * y / (double)HEIGHT);
	ray->scene_pixel_x = x * aspect_ratio * scene->fov;
	ray->scene_pixel_y = y * scene->fov;
	origin = vector_add(vector_add(scene->v_cam_canvas, \
	scalar_mult(scene->v_width, ray->scene_pixel_x, gc), gc), \
	scalar_mult(scene->v_height, ray->scene_pixel_y, gc), gc);
	ray->origin = &(t_vec){origin->vec_x, origin->vec_y, origin->vec_z};
	dir = normalize(vector_sub(origin, scene->pov, gc), gc);
	ray->direction = &(t_vec){dir->vec_x, dir->vec_y, dir->vec_z};
	add_to_garb_col(gc, ray);
	add_to_garb_col(gc, ray->origin);
	add_to_garb_col(gc, ray->direction);
	return (ray);
}

// void	init_graphics(t_main_rt *main_rt)
// {
// 	main_rt->mlx = mlx_init(WIDTH, HEIGHT, "RayTracer", true);
// 	if (!main_rt->mlx)
// 		print_msg(1, "window initialization failure");
// }

// mlx_t	*post_processing(t_main_rt *main_rt)
// {
// 	init_viewport(main_rt);
// 	init_graphics(main_rt);
// 	// hook keypress
// 	// hook quit
// 	render(main_rt);
// 	mlx_loop(main_rt);
// }
