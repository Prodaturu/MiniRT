#include "../include/minirt.h"

t_color	trace_lighting(const t_scene *scene, const t_hit *hit)
{
	t_light	*light;
	t_vec	light_vec;
	t_vec	light_dir;
	double	light_distance;
	double	diffuse_factor;
	t_color	result;
	t_color	diffuse;

	result = color_scale(color_mul(hit->color, scene->ambient.color),
			scene->ambient.ratio);
	light = scene->lights;
	while (light != NULL)
	{
		light_vec = vec_sub(light->position, hit->point);
		light_distance = vec_length(light_vec);
		light_dir = vec_normalize(light_vec);
		diffuse_factor = vec_dot(hit->normal, light_dir);
		if (diffuse_factor > 0.0
			&& !is_in_shadow(scene, hit->point, light_dir, light_distance))
		{
			diffuse = color_scale(color_mul(hit->color, light->color),
					light->ratio * diffuse_factor);
			result = color_add(result, diffuse);
		}
		light = light->next;
	}
	return (color_clamp(result));
}

t_color	trace_ray(const t_scene *scene, t_ray ray)
{
	t_hit	hit;

	if (!scene_hit(scene, ray, EPSILON, INFINITY, &hit))
		return ((t_color){0.0, 0.0, 0.0});
	return (trace_lighting(scene, &hit));
}
