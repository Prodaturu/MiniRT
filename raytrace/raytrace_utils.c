#include "../include/minirt.h"

static bool	hit_sphere(const t_object *obj, t_ray ray, double t_min, double t_max, t_hit *hit)
{
	t_vec	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	root;

	oc = vec_sub(ray.origin, obj->position);
	a = vec_dot(ray.direction, ray.direction);
	b = 2.0 * vec_dot(oc, ray.direction);
	c = vec_dot(oc, oc) - obj->radius * obj->radius;
	discriminant = b * b - 4.0 * a * c;
	if (discriminant < 0.0)
		return (false);
	root = (-b - sqrt(discriminant)) / (2.0 * a);
	if (root <= t_min || root >= t_max)
	{
		root = (-b + sqrt(discriminant)) / (2.0 * a);
		if (root <= t_min || root >= t_max)
			return (false);
	}
	hit->hit = true;
	hit->t = root;
	hit->point = vec_add(ray.origin, vec_scale(ray.direction, root));
	hit->normal = vec_normalize(vec_sub(hit->point, obj->position));
	hit->color = obj->color;
	return (true);
}

static bool	hit_plane(const t_object *obj, t_ray ray, double t_min, double t_max, t_hit *hit)
{
	double	denom;
	double	root;

	denom = vec_dot(obj->direction, ray.direction);
	if (fabs(denom) < EPSILON)
		return (false);
	root = vec_dot(vec_sub(obj->position, ray.origin), obj->direction) / denom;
	if (root <= t_min || root >= t_max)
		return (false);
	hit->hit = true;
	hit->t = root;
	hit->point = vec_add(ray.origin, vec_scale(ray.direction, root));
	hit->normal = obj->direction;
	if (vec_dot(hit->normal, ray.direction) > 0.0)
		hit->normal = vec_scale(hit->normal, -1.0);
	hit->color = obj->color;
	return (true);
}

static void	make_basis(t_vec normal, t_vec *u, t_vec *v)
{
	t_vec	helper;

	helper = (t_vec){0.0, 1.0, 0.0};
	if (fabs(vec_dot(normal, helper)) > 0.999)
		helper = (t_vec){1.0, 0.0, 0.0};
	*u = vec_normalize(vec_cross(normal, helper));
	*v = vec_normalize(vec_cross(*u, normal));
}

static bool	hit_square(const t_object *obj, t_ray ray, double t_min, double t_max, t_hit *hit)
{
	t_hit	plane_hit;
	t_vec	u;
	t_vec	v;
	t_vec	local;
	double	half;

	if (!hit_plane(obj, ray, t_min, t_max, &plane_hit))
		return (false);
	make_basis(obj->direction, &u, &v);
	local = vec_sub(plane_hit.point, obj->position);
	half = obj->size * 0.5;
	if (fabs(vec_dot(local, u)) > half || fabs(vec_dot(local, v)) > half)
		return (false);
	*hit = plane_hit;
	return (true);
}

static bool	hit_triangle(const t_object *obj, t_ray ray, double t_min, double t_max, t_hit *hit)
{
	t_vec	edge1;
	t_vec	edge2;
	t_vec	h;
	t_vec	s;
	t_vec	q;
	double	a;
	double	f;
	double	u;
	double	v;
	double	t;

	edge1 = vec_sub(obj->vertex_b, obj->position);
	edge2 = vec_sub(obj->vertex_c, obj->position);
	h = vec_cross(ray.direction, edge2);
	a = vec_dot(edge1, h);
	if (fabs(a) < EPSILON)
		return (false);
	f = 1.0 / a;
	s = vec_sub(ray.origin, obj->position);
	u = f * vec_dot(s, h);
	if (u < 0.0 || u > 1.0)
		return (false);
	q = vec_cross(s, edge1);
	v = f * vec_dot(ray.direction, q);
	if (v < 0.0 || u + v > 1.0)
		return (false);
	t = f * vec_dot(edge2, q);
	if (t <= t_min || t >= t_max)
		return (false);
	hit->hit = true;
	hit->t = t;
	hit->point = vec_add(ray.origin, vec_scale(ray.direction, t));
	hit->normal = obj->direction;
	if (vec_dot(hit->normal, ray.direction) > 0.0)
		hit->normal = vec_scale(hit->normal, -1.0);
	hit->color = obj->color;
	return (true);
}

static bool	hit_cylinder_cap(const t_object *obj, t_ray ray, double t_plane, t_vec cap_center, t_hit *hit)
{
	t_vec	point;

	if (t_plane <= EPSILON)
		return (false);
	point = vec_add(ray.origin, vec_scale(ray.direction, t_plane));
	if (vec_length(vec_sub(point, cap_center)) > obj->radius + EPSILON)
		return (false);
	hit->hit = true;
	hit->t = t_plane;
	hit->point = point;
	hit->color = obj->color;
	return (true);
}

static bool	hit_cylinder_caps(const t_object *obj, t_ray ray, double t_min, double t_max, t_hit *best)
{
	t_vec	top;
	t_vec	bottom;
	t_vec	cap_normal;
	double	denom;
	double	t_plane;
	t_hit	temp;

	top = vec_add(obj->position, vec_scale(obj->direction, obj->height * 0.5));
	bottom = vec_sub(obj->position, vec_scale(obj->direction, obj->height * 0.5));
	cap_normal = obj->direction;
	denom = vec_dot(cap_normal, ray.direction);
	if (fabs(denom) >= EPSILON)
	{
		t_plane = vec_dot(vec_sub(top, ray.origin), cap_normal) / denom;
		if (t_plane > t_min && t_plane < t_max && hit_cylinder_cap(obj, ray, t_plane, top, &temp))
		{
			temp.normal = cap_normal;
			if (vec_dot(temp.normal, ray.direction) > 0.0)
				temp.normal = vec_scale(temp.normal, -1.0);
			*best = temp;
			t_max = temp.t;
		}
		t_plane = vec_dot(vec_sub(bottom, ray.origin), cap_normal) / denom;
		if (t_plane > t_min && t_plane < t_max && hit_cylinder_cap(obj, ray, t_plane, bottom, &temp))
		{
			temp.normal = vec_scale(cap_normal, -1.0);
			if (vec_dot(temp.normal, ray.direction) > 0.0)
				temp.normal = vec_scale(temp.normal, -1.0);
			*best = temp;
			return (true);
		}
	}
	return (best->hit);
}

static bool	hit_cylinder_side(const t_object *obj, t_ray ray, double t_min, double t_max, t_hit *hit)
{
	t_vec	oc;
	t_vec	d_perp;
	t_vec	oc_perp;
	double	axis_dot_d;
	double	axis_dot_oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	root;
	double	proj;

	oc = vec_sub(ray.origin, obj->position);
	axis_dot_d = vec_dot(ray.direction, obj->direction);
	axis_dot_oc = vec_dot(oc, obj->direction);
	d_perp = vec_sub(ray.direction, vec_scale(obj->direction, axis_dot_d));
	oc_perp = vec_sub(oc, vec_scale(obj->direction, axis_dot_oc));
	a = vec_dot(d_perp, d_perp);
	b = 2.0 * vec_dot(d_perp, oc_perp);
	c = vec_dot(oc_perp, oc_perp) - obj->radius * obj->radius;
	discriminant = b * b - 4.0 * a * c;
	if (fabs(a) < EPSILON || discriminant < 0.0)
		return (false);
	root = (-b - sqrt(discriminant)) / (2.0 * a);
	while (root > t_min && root < t_max)
	{
		proj = axis_dot_oc + root * axis_dot_d;
		if (fabs(proj) <= obj->height * 0.5 + EPSILON)
		{
			hit->hit = true;
			hit->t = root;
			hit->point = vec_add(ray.origin, vec_scale(ray.direction, root));
			hit->normal = vec_normalize(vec_sub(vec_sub(hit->point, obj->position),
						vec_scale(obj->direction, proj)));
			hit->color = obj->color;
			return (true);
		}
		root = (-b + sqrt(discriminant)) / (2.0 * a);
		if (root <= t_min || root >= t_max)
			break ;
		proj = axis_dot_oc + root * axis_dot_d;
		if (fabs(proj) <= obj->height * 0.5 + EPSILON)
		{
			hit->hit = true;
			hit->t = root;
			hit->point = vec_add(ray.origin, vec_scale(ray.direction, root));
			hit->normal = vec_normalize(vec_sub(vec_sub(hit->point, obj->position),
						vec_scale(obj->direction, proj)));
			hit->color = obj->color;
			return (true);
		}
		break ;
	}
	return (false);
}

static bool	hit_cylinder(const t_object *obj, t_ray ray, double t_min, double t_max, t_hit *hit)
{
	t_hit	best;

	memset(&best, 0, sizeof(best));
	if (hit_cylinder_side(obj, ray, t_min, t_max, &best))
		t_max = best.t;
	if (hit_cylinder_caps(obj, ray, t_min, t_max, &best))
	{
		*hit = best;
		return (true);
	}
	if (best.hit)
	{
		*hit = best;
		return (true);
	}
	return (false);
}

bool	scene_hit(const t_scene *scene, t_ray ray, double t_min, double t_max, t_hit *hit)
{
	const t_object	*object;
	t_hit			temp;
	bool			found;

	found = false;
	object = scene->objects;
	while (object != NULL)
	{
		memset(&temp, 0, sizeof(temp));
		if ((object->type == OBJ_SPHERE && hit_sphere(object, ray, t_min, t_max, &temp))
			|| (object->type == OBJ_PLANE && hit_plane(object, ray, t_min, t_max, &temp))
			|| (object->type == OBJ_CYLINDER && hit_cylinder(object, ray, t_min, t_max, &temp))
			|| (object->type == OBJ_SQUARE && hit_square(object, ray, t_min, t_max, &temp))
			|| (object->type == OBJ_TRIANGLE && hit_triangle(object, ray, t_min, t_max, &temp)))
		{
			found = true;
			t_max = temp.t;
			*hit = temp;
		}
		object = object->next;
	}
	return (found);
}

bool	is_in_shadow(const t_scene *scene, t_vec point, t_vec light_dir, double light_distance)
{
	t_ray	shadow_ray;
	t_hit	hit;

	shadow_ray.origin = vec_add(point, vec_scale(light_dir, EPSILON * 50.0));
	shadow_ray.direction = light_dir;
	return (scene_hit(scene, shadow_ray, EPSILON, light_distance - EPSILON, &hit));
}
