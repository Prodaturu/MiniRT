/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 22:21:20 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/25 23:02:49 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	scene_render(t_main_rt *main_rt);

/**
 * @brief calculates and returns a ray from the camera
 * to a specific pixel on the scene's canvas in a 3D rendering context.
 * It takes the scene and the pixel coordinates (x, y) as input.
 * The process involves:
 * Allocating memory for a new ray and its components
 * Calculating the aspect ratio of the scene
 * Adjusting input pixel co-ords (x, y) based on the aspect ratio 
 * and scene's FOV to map them correctly onto the scene's canvas.
 * Compute rays origin and co-ords based on the scene's camera and canvas
 * dir is normalized from POV to calculated origin
 * adds to garbage collector
 * @return t_ray* returns the calculated ray
 * 
 * @param scene the scene struct
 * @param x x coordinate of the pixel
 * @param y y coordinate of the pixel
 */
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
			ray = get_ray(scene, x, y);
			color = ray_color(ray, scene, main_rt->parser->light);
			printf("color: r %f\t g %f\t b %f a %f\n", color->red, \
			color->green, color->blue, color->alpha);
			ray->col = get_rgba(color->red, color->green, color->blue, \
			color->alpha);
			printf("ray->col: %d\n", ray->col);
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
	t_vec		*origin;
	t_vec		*dir;
	double		aspect_ratio;

	ray = malloc(sizeof(t_ray));
	ray->origin = malloc(sizeof(t_vec));
	ray->direction = malloc(sizeof(t_vec));
	gc = scene->garbage_col;
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	ray->scene_pixel_x = (2 * ((x + 0.5) / WIDTH) - 1) * \
	scene->fov * aspect_ratio;
	ray->scene_pixel_y = (1 - 2 * ((y + 0.5) / HEIGHT)) * scene->fov;
	origin = scene->pov;
	dir = normalize(get_vec(ray->scene_pixel_x * scene->v_width->vec_x + \
	ray->scene_pixel_y * scene->v_height->vec_x + scene->v_cam_canvas->vec_x, \
	ray->scene_pixel_x * scene->v_width->vec_y + ray->scene_pixel_y * \
	scene->v_height->vec_y + scene->v_cam_canvas->vec_y, \
	ray->scene_pixel_x * scene->v_width->vec_z + ray->scene_pixel_y * \
	scene->v_height->vec_z + scene->v_cam_canvas->vec_z, gc), gc);
	ray->origin = (t_vec *)origin;
	ray->direction = (t_vec *)dir;
	add_to_garb_col(gc, ray);
	return (ray);
}

// t_ray *get_ray(t_scene *scene, double x, double y) {
//     t_ray *ray = malloc(sizeof(t_ray));
//     ray->origin = malloc(sizeof(t_vec));
//     ray->direction = malloc(sizeof(t_vec));
//     t_garbage *gc = scene->garbage_col;

//     // Aspect ratio and normalized device coordinates
//     double aspect_ratio = (double)WIDTH / (double)HEIGHT;
//     x = (2 * x / (double)WIDTH - 1) * aspect_ratio;
//     y = (1 - 2 * y / (double)HEIGHT);

//     // Calculate ray direction
//     ray->scene_pixel_x = x * aspect_ratio * scene->fov;
//     ray->scene_pixel_y = y * scene->fov;
//     t_vec *origin = vector_add(vector_add(scene->v_cam_canvas, 
//                    scalar_mult(scene->v_width, ray->scene_pixel_x, gc), gc), 
//                    scalar_mult(scene->v_height, ray->scene_pixel_y, gc), gc);
//     ray->origin = &(t_vec){origin->vec_x, origin->vec_y, origin->vec_z};
//     t_vec *dir = normalize(vector_sub(origin, scene->pov, gc), gc);
//     ray->direction = &(t_vec){dir->vec_x, dir->vec_y, dir->vec_z};

//     // Register with garbage collector
//     add_to_garb_col(gc, ray);
//     add_to_garb_col(gc, ray->origin);
//     add_to_garb_col(gc, ray->direction);

//     return ray;
// }

// void	init_graphics(t_main_rt *main_rt)
// {
// 	t_ray		*ray;
// 	t_vector	*origin;
// 	t_vector	*dir;
// 	t_garbage	*gc;
// 	double		aspect_ratio;

// 	ray = malloc(sizeof(t_ray));
// 	if (!ray)
// 		return (ft_putendl_fd("Error: malloc error", 2), (void *)0);
// 	gc = scene->garbage_col;
// 	aspect_ratio = (double)WIDTH / (double)HEIGHT;
// 	ray->scene_pixel_x = (2 * ((x + 0.5) / WIDTH) - 1) * \
// 	tan(scene->fov / 2 * M_PI / 180) * aspect_ratio;
// 	ray->scene_pixel_y = (1 - 2 * ((y + 0.5) / HEIGHT)) * \
// 	tan(scene->fov / 2 * M_PI / 180);
// 	origin = scene->pov;
// 	dir = get_vec(scene->v_cam_canvas->vec_x + ray->scene_pixel_x * \
// 	scene->v_width->vec_x + ray->scene_pixel_y * scene->v_height->vec_x, \
// 	scene->v_cam_canvas->vec_y + ray->scene_pixel_x * scene->v_width->vec_y + \
// 	ray->scene_pixel_y * scene->v_height->vec_y, scene->v_cam_canvas->vec_z + \
// 	ray->scene_pixel_x * scene->v_width->vec_z + ray->scene_pixel_y * \
// 	scene->v_height->vec_z, gc);
// 	// dir = normalize(dir, gc);
// 	ray->origin = (t_vec *)origin;
// 	ray->direction = (t_vec *)dir;
// 	add_to_garb_col(gc, ray);
// 	return (ray);
// }
