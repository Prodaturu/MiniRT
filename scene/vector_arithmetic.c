#include "../include/minirt.h"

t_vec	vec_add(t_vec a, t_vec b)
{
	return ((t_vec){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vec	vec_sub(t_vec a, t_vec b)
{
	return ((t_vec){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vec	vec_scale(t_vec v, double scale)
{
	return ((t_vec){v.x * scale, v.y * scale, v.z * scale});
}

double	vec_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec	vec_cross(t_vec a, t_vec b)
{
	return ((t_vec){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	});
}

double	vec_length(t_vec v)
{
	return (sqrt(vec_dot(v, v)));
}

t_vec	vec_normalize(t_vec v)
{
	double	length;

	length = vec_length(v);
	if (length < EPSILON)
		return ((t_vec){0.0, 0.0, 0.0});
	return (vec_scale(v, 1.0 / length));
}
