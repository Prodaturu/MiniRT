/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 18:28:49 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/25 22:54:18 by sprodatu         ###   ########.fr       */
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


t_color *ray_color(t_ray *ray, t_scene *scene, t_light *light)
{
    t_vec *hit_point;
    t_vec *light_dir = normalize(vector_sub(light->position, hit_point, scene->garbage_col), scene->garbage_col);
    double light_distance = vector_length(vector_sub(light->position, hit_point, scene->garbage_col));
    int in_shadow;

	hit_point = ray->hit_point; // Assume this is the intersection point
    t_ray *shadow_ray = malloc(sizeof(t_ray));
    shadow_ray->origin = hit_point;
    shadow_ray->direction = light_dir;

	in_shadow = is_in_shadow(scene, shadow_ray, light_distance);

    t_color *final_color;
    if (in_shadow)
        final_color = create_color(0, 0, 0); // Or some ambient color
    else
        final_color = calculate_lighting(hit_point, light, scene);

    free(shadow_ray);
    return final_color;
}

// t_color	*ray_color(t_ray *ray, t_scene *scene, t_light_rt *light)
// {
// 	t_hit		rec;
// 	// t_vec		*unit_direction;
// 	t_color		*diffuse;
// 	t_color		*background;
// 	int			in_shadow;
// 	t_ray		*shadow_ray;

// 	if (hit_objects(scene->objects, ray, YPSILON, &rec))
// 	{
// 		diffuse = diffuse_lighting(scene, light, rec);
// 		return (diffuse);
// 	}
// 	background = scene->background_color;
// 	// return (background);
// 	shadow_ray->origin = hit_point;
//     shadow_ray->direction = light_dir;
// 	in_shadow = is_in_shadow(scene, shadow_ray, light_distance);

//     t_color *final_color;
//     if (in_shadow) {
//         final_color = create_color(0, 0, 0); // Or some ambient color
//     } else {
//         // Calculate the normal shading here
//         final_color = calculate_lighting(hit_point, light, scene);
//     }

//     free(shadow_ray);
//     return final_color;
// }

// background = lerp((t_color){1.0, 1.0, 1.0}, (t_color){0.5, 0.7, 1.0}, t);
//linear interpolation function in case when we need to blend two colors
// t_color	lerp(t_color a, t_color b, double t)
// {
// 	return ((t_color){
// 		(1.0 - t) * a.red + t * b.red,
// 		(1.0 - t) * a.green + t * b.green,
// 		(1.0 - t) * a.blue + t * b.blue});
// }
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
	while (i < objects->count)
	{
		if (hit(objects->object[i], ray, t_min, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->color = &(t_col){(double)objects->object[i].color->r, \
			(double)objects->object[i].color->g, \
			(double)objects->object[i].color->b};
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

// t_vec	*normalize(t_vec *v)
// {
// 	double	mag;

// 	mag = sqrt(v.vec_x * v.vec_x + v.vec_y * v.vec_y + v.vec_z * v.vec_z);
// 	return ((t_vec){v.vec_x / mag, v.vec_y / mag, v.vec_z / mag});
// }
double	dot(t_vec a, t_vec b)
{
	return (a.vec_x * b.vec_x + a.vec_y * b.vec_y + a.vec_z * b.vec_z);
}

t_color	*diffuse_lighting(t_scene *scene, t_light_rt *light, t_hit rec)
{
	t_vec		*light_dir;
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
	t_vec	center;
	t_vec	point;

	(void)rec;
	(void)t_min;
	center = (t_vec){object.sphere->center->co_x, \
	object.sphere->center->co_y, object.sphere->center->co_z};
	point = (t_vec){ray->origin->vec_x, ray->origin->vec_y, \
	ray->origin->vec_z};
	if (object.type == SPHERE)
		return (is_on_sphere(center, object.sphere->diameter, \
		point));
		// , ray, t_min, rec));
	// if (object.type == PLANE)
	// 	return (hit_plane(object, ray, t_min, rec));
	// if (object.type == CYLINDER)
	// 	return (hit_cylinder(object, ray, t_min, rec));
	return (false);
}
