/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 00:29:21 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/21 00:23:48 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

//function with center and point on canvas as input
//for sphere call sphere->center
//for plane call plane->coord
//for cylinder call cylinder->center
int	point_check(t_coord_rt *object_center, int x, int y, t_main_rt *main_rt)
{
	t_vector	point;

	point.vec_x = x;
	point.vec_y = y;
	point.vec_z = object_center->co_z;
	return (0);
}
