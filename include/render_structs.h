#ifndef RENDER_STRUCTS_H
# define RENDER_STRUCTS_H

# include <stdbool.h>

typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_ray
{
	t_vec	origin;
	t_vec	direction;
}	t_ray;

typedef struct s_hit
{
	bool	hit;
	double	t;
	t_vec	point;
	t_vec	normal;
	t_color	color;
}	t_hit;

#endif
