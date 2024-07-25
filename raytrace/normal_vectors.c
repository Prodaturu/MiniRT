/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:25:21 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/24 00:58:08 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vec	spr_reflect(t_vec in_dir, t_vec normal, t_garbage *gc)
{
	t_vec	reflected_vec;
	double	dot;

	dot = dot(in_dir, normal, gc);
	reflected_vec = vector_sub(in_dir, scalar_mult(normal, 2 * dot, gc), gc);
	return (reflected_vec);
}

t_vec	sphere_reflected_vec(t_main_rt *rt, t_ray *in_ray, t_sphere_rt *spr)
{
	t_vec	normal_from_center;
	t_vec	reflected_vec;

	normal_from_center = vector_sub(in_ray->origin, spr->center, rt->gc);
	normal_from_center = normalize(normal_from_center, rt->gc);
	reflected_vec = spr_reflect(in_ray->dir, normal_from_center, rt->gc);
}
