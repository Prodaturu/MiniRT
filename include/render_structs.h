/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:06:29 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/22 23:09:24 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_STRUCTS_H
# define RENDER_STRUCTS_H

typedef struct s_vec
{
	double		vec_x;
	double		vec_y;
	double		vec_z;
}				t_vec;

typedef struct s_col
{
	double		r;
	double		g;
	double		b;
}				t_col;

typedef struct s_hit
{
	t_vec			normal;
	t_vec			col_point;
	t_col			*color;
	struct t_hit	*record;
	struct t_hit	*next;
	double			t;
}				t_hit;

/**
 * @param scene_pixel_x x coordinates for scene pixel on canvas
 * @param scene_pixel_y y coordinates for scene pixel on canvas
 * @param t_max 
 */
typedef struct s_ray
{
	t_vec	*origin;
	t_vec	*direction;
	t_hit	*hit;
	double	scene_pixel_x;
	double	scene_pixel_y;
	double	t_max;
	int		col;
}				t_ray;

#endif