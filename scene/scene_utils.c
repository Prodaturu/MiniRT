/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 19:30:16 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/23 18:33:09 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vec	*scalar_mult(t_vec *a, double c, t_garbage *gc);
t_vec	*set_orientation(t_vec_rt *orientation, t_garbage *gc);
t_vec	*set_pov(t_pov_rt *pov, t_garbage *gc);

t_vec	*scalar_mult(t_vec *a, double c, t_garbage *gc)
{
	t_vec	*result;

	result = (t_vec *)malloc(sizeof(t_vec));
	if (result == NULL)
		err_msg(gc, 1, "error allocating vector\n", true);
	else
		add_to_garb_col(gc, result);
	result->vec_x = c * a->vec_x;
	result->vec_y = c * a->vec_y;
	result->vec_z = c * a->vec_z;
	return (result);
}

t_vec	*set_pov(t_pov_rt *pov, t_garbage *gc)
{
	t_vec	*pov_vec;

	pov_vec = get_vec(pov->pv_x, pov->pv_y, pov->pv_z, gc);
	return (pov_vec);
}

t_vec	*set_orientation(t_vec_rt *orientation, t_garbage *gc)
{
	t_vec	*orientation_vec;

	orientation_vec = get_vec(orientation->vc_x, orientation->vc_y, \
	orientation->vc_z, gc);
	return (orientation_vec);
}
