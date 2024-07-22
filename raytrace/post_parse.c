/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 22:21:20 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/21 01:13:34 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

/*
void init_camera(t_scene *scene, t_camera *cam, t_garbage_collector *gc)
{
    double fov_radians;
    t_vector *aux;
    double half_diag;

    if (!is_vector_normal(scene->camera.orientation, gc))
        exit_function(gc, "camera vector is not normal\n", 1, true);
    (*cam).width = WIDTH;
    (*cam).height = (int)(((*cam).width) / (16.9 / 9.0));
    (*cam).point = point(scene->camera.point->coordinate[0], scene->camera.point->coordinate[1], scene->camera.point->coordinate[2], gc);
    (*cam).orientation = vector(scene->camera.orientation->coordinate[0], scene->camera.orientation->coordinate[1], scene->camera.orientation->coordinate[2], gc);
    (*cam).fov = scene->camera.fov;
    set_atributes(&half_diag, &fov_radians, cam);
    set_normal_vector(cam, &aux, gc);
    set_v_width_length(aux, cam, gc);
    aux = vector_subtract((*cam).v_height, (*cam).v_width, gc);
    (*cam).pixel00 = vector_add((*cam).v_cam_canvas, aux, gc);
    (*cam).v_width = normalize((*cam).v_width, gc);
    (*cam).v_height = normalize((*cam).v_height, gc);
}
*/

mlx_t	init_viewport(t_parser *main_rt)
{
	t_vector	help_vec;
	double		half_diag;

	main_rt->cam->pixel_width = WIDTH;
	main_rt->cam->pixel_height = HEIGHT;
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
