/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:28:49 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/23 03:48:59 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_color	*ray_color(t_ray *ray, t_scene *scene, t_light_rt *light);
bool	hit_objects(t_objects *objects, t_ray *ray, double t_min, t_hit *rec);
t_color	*diffuse_lighting(t_scene *scene, t_light_rt *light, t_hit rec);
bool	hit(t_object object, t_ray *ray, double t_min, t_hit *rec);

// color objektu l 29
// Oświetlenie Lambertowskie (Diffuse) l 30
// Dodanie cienia (opcjonalne)l 34
// Jeśli jest cień, zmniejsz intensywność l 38
// Kolor tła l 42

t_color	*ray_color(t_ray *ray, t_scene *scene, t_light_rt *light)
{
	t_hit		rec;
	// t_vector	*unit_direction;
	t_color		*diffuse;
	t_color		*background;
	// double		t;

	if (scene->depth <= 0)
		return (&(t_color){0.0, 0.0, 0.0, 255.0});
	if (!hit_objects(scene->objects, ray, YPSILON, &rec))
	{
		diffuse = diffuse_lighting(scene, light, rec);
		// printf("diff: r %f\t g %f\t b %f\n", diffuse->red, \
		// diffuse->green, diffuse->blue);
		return (diffuse);
	}
	// unit_direction = normalize(get_vec(ray->direction->vec_x, 
	// ray->direction->vec_y, ray->direction->vec_z, scene->garbage_col), 
	// scene->garbage_col);
	// t = 0.5 * (unit_direction->vec_y + 1.0);
	background = scene->background_color;
	return (background);
}
// background = lerp((t_color){1.0, 1.0, 1.0}, (t_color){0.5, 0.7, 1.0}, t);
//linear interpolation function in case when we need to blend two colors
// t_color	lerp(t_color a, t_color b, double t)
// {
// 	return ((t_color){
// 		(1.0 - t) * a.red + t * b.red,
// 		(1.0 - t) * a.green + t * b.green,
// 		(1.0 - t) * a.blue + t * b.blue});
// }

t_col	*set_obj_color(t_object object, t_col *color)
{
	color = malloc(sizeof(t_col));
	if (!color)
		return (&(t_col){0.0, 0.0, 0.0});
	color->r = object.sphere->color->r;
	color->g = object.sphere->color->g;
	color->b = object.sphere->color->b;
	return (color);
}

t_col	*set_color(t_color_rt *color, t_col *rec_color)
{
	rec_color = malloc(sizeof(t_col));
	if (!color)
		return (&(t_col){0.0, 0.0, 0.0});
	rec_color->r = color->r;
	rec_color->g = color->g;
	rec_color->b = color->b;
	return (rec_color);
}

bool	hit_objects(t_objects *objects, t_ray *ray, double t_min, t_hit *rec)
{
	t_hit	temp_rec;
	double	t_max;
	bool	hit_anything;
	double	closest_so_far;
	int		i;

	i = 0;
	t_max = INFINITY;
	closest_so_far = t_max;
	hit_anything = false;
	ray->t_max = t_max;
	printf("objects->count: %d\n", objects->count);
	while (i <= objects->count)
	{
		if (!hit(objects->object[i], ray, t_min, &temp_rec))
		{
			
			printf("iteracja: %d\n", i);
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			printf("%p\n", rec->color);
			printf("%p\n", objects->object);
			rec->color = set_color(objects->object->color, rec->color);
			printf("obj color%d\n", objects->object->color->r);
			printf("rec col%f\n", rec->color->r);
			// printf("%p\n", rec->color);
		}
		i++;
	}
	return (hit_anything);
}

t_color	*color_multiply_scalar(t_color *color, double scalar)
{
	return (&(t_color){color->red * scalar, color->green * scalar, \
	color->blue * scalar, color->alpha * scalar});
}

// t_vector	*normalize(t_vector *v)
// {
// 	double	mag;

// 	mag = sqrt(v.vec_x * v.vec_x + v.vec_y * v.vec_y + v.vec_z * v.vec_z);
// 	return ((t_vector){v.vec_x / mag, v.vec_y / mag, v.vec_z / mag});
// }

double	dot(t_vector a, t_vector b)
{
	return (a.vec_x * b.vec_x + a.vec_y * b.vec_y + a.vec_z * b.vec_z);
}

t_color	*diffuse_lighting(t_scene *scene, t_light_rt *light, t_hit rec)
{
	t_vector	*light_dir;
	double		light_intensity;
	t_color		*material_color;
	t_color		*diffuse;
	t_ray		shadow_ray;

	light_dir = get_vec(light->coord->co_x - rec.col_point.vec_x, \
	light->coord->co_y - rec.col_point.vec_y, \
	light->coord->co_z - rec.col_point.vec_z, scene->garbage_col);
	light_dir = normalize(light_dir, scene->garbage_col);
	light_intensity = fmax(0.0, (light->coord->co_x * rec.col_point.vec_x \
	+ light->coord->co_y * rec.col_point.vec_y + light->coord->co_z \
	* rec.col_point.vec_z)) * light->ratio;
	material_color = &(t_color){rec.color->r, rec.color->g, rec.color->b, \
	light_intensity};
	diffuse = color_multiply_scalar(material_color, light_intensity);
	shadow_ray.origin = &rec.col_point;
	shadow_ray.direction = &(t_vec){light_dir->vec_x, light_dir->vec_y, \
	light_dir->vec_z};
	if (hit_objects(scene->objects, &shadow_ray, YPSILON, &rec))
	{
		diffuse = color_multiply_scalar(diffuse, 0.5);
		// shadow_ray = 
	}
	return (diffuse);
}

bool	hit(t_object object, t_ray *ray, double t_min, t_hit *rec)
{
	t_vector	center;
	// t_vector	point;

	(void)rec;
	(void)t_min;
	(void)ray;
	center = (t_vector){object.sphere->center->co_x, \
	object.sphere->center->co_y, object.sphere->center->co_z};
	// point = (t_vector){ray->origin->vec_x, ray->origin->vec_y, \
	// ray->origin->vec_z};
	// if (object.type == SPHERE)
	// 	return (is_on_sphere(center, object.sphere->diameter, \
	// 	point));
	return (false);
}
		// , ray, t_min, rec));
	// if (object.type == PLANE)
	// 	return (hit_plane(object, ray, t_min, rec));
	// if (object.type == CYLINDER)
	// 	return (hit_cylinder(object, ray, t_min, rec));
