/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:29:21 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/21 01:12:54 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

//function with center and point on canvas as input
int	point_check(t_coord_rt object_center, int x, int y, t_main_rt *main_rt)
{
	t_vector	point;

	point.vec_x = x;
	point.vec_y = y;
	//point.vec_z = object_center->(with)z;
	(void)object_center;
	//for sphere call sphere->center
	//for plane call plane->coord
	//for cylinder call cylinder->center

	return (0);
}
