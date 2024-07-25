/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:46:28 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/23 18:35:04 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vec		*get_vec(double x, double y, double z, t_garbage *gc);
int			init_scene_struct(t_main_rt *main_rt, t_garbage *gc);
void		atributs_setter(double *half_diag, double *fov_rad, t_scene *scene);
void		norm_vec_setter(t_scene *scene, t_vec **help_vec, t_garbage *gc);
void		set_v_width_length(t_vec *help_vec, t_scene *sc, t_garbage *gc);

t_vec	*get_vec(double x, double y, double z, t_garbage *gc)
{
	t_vec	*vec;

	vec = (t_vec *)malloc(sizeof(t_vec));
	if (!vec)
		return (ft_putendl_fd("Error: malloc error", 2), (void *)0);
	vec->vec_x = x;
	vec->vec_y = y;
	vec->vec_z = z;
	add_to_garb_col(gc, vec);
	return (vec);
}

void	atributs_setter(double *half_diag, double *fov_radians, t_scene *scene)
{
	scene->pixel_width = WIDTH;
	scene->pixel_height = HEIGHT;
	*half_diag = sqrt(pow(scene->pixel_width, 2) + \
		pow(scene->pixel_height, 2)) / 2;
	*fov_radians = scene->fov * M_PI / 180;
	scene->focal_length = *half_diag / tan(*fov_radians / 2);
}

void	norm_vec_setter(t_scene *scene, t_vec **help_vec, t_garbage *gc)
{
	if (scene->pov->vec_x == 0.0f && (scene->pov->vec_y == 1.0f \
		|| scene->pov->vec_y == -1.0f) && scene->pov->vec_z == 0.0f)
		*help_vec = get_vec(0, 0.0, -1.0, gc);
	else
		*help_vec = get_vec(0.0, 1.0, 0.0, gc);
}

void	set_v_width_length(t_vec *help_vec, t_scene *sc, t_garbage *gc)
{
	sc->v_width = normalize(cross(help_vec, sc->orientation, gc), gc);
	sc->v_width = scalar_mult(sc->v_width, (sc->pixel_width) \
	* 0.5, gc);
	sc->v_height = normalize(cross(sc->orientation, sc->v_width, gc), gc);
	sc->v_height = scalar_mult(sc->v_height, (sc->pixel_height) * 0.5, gc);
	sc->v_cam_canvas = scalar_mult(sc->orientation, sc->focal_length, gc);
	sc->v_cam_canvas = vector_add(sc->v_cam_canvas, sc->pov, gc);
}

int	init_scene_struct(t_main_rt *main_rt, t_garbage *gc)
{
	t_vec		*help_vec;
	t_scene		*scene;
	t_objects	*objects;
	double		fov_radians;
	double		half_diag;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (1);
	add_to_garb_col(gc, scene);
	objects = objects_init(main_rt, gc);
	help_vec = NULL;
	scene->fov = main_rt->parser->cam->fov;
	scene->pov = set_pov(main_rt->parser->cam->pov, gc);
	scene->orientation = set_orientation(main_rt->parser->cam->orient_vec, gc);
	norm_vec_setter(scene, &help_vec, gc);
	set_v_width_length(help_vec, scene, gc);
	help_vec = vector_sub(scene->v_height, scene->v_width, gc);
	scene->start_pixel = vector_add(scene->v_cam_canvas, help_vec, gc);
	scene->v_width = normalize(scene->v_width, gc);
	scene->v_height = normalize(scene->v_height, gc);
	scene->background_color = &(t_color){main_rt->parser->amb->color->r, \
	main_rt->parser->amb->color->g, main_rt->parser->amb->color->b, \
	255.0 / main_rt->parser->amb->ratio};
	main_rt->scene = scene;
	atributs_setter(&half_diag, &fov_radians, scene);
	return (scene->garbage_col = gc, scene->depth = 2, 0);
}
