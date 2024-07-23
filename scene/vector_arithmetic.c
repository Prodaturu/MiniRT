/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_arithmetic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:40:46 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/22 22:51:56 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vector	*normalize(t_vector *vector, t_garbage *gc);
t_vector	*vector_add(t_vector *vector, t_vector *help_vec, t_garbage *gc);
t_vector	*vector_sub(t_vector *v_height, t_vector *v_width, t_garbage *gc);
t_vector	*vector_mult(t_vector *vector, double mult, t_garbage *gc);
t_vector	*cross(t_vector *a, t_vector *b, t_garbage *gc);

t_vector	*cross(t_vector *a, t_vector *b, t_garbage *gc)
{
	t_vector	*result;

	result = (t_vector *) malloc(sizeof(t_vector));
	if (result == NULL)
		err_msg(gc, 1, "error allocating vector\n", true);
	else
		add_to_garb_col(gc, result);
	result->vec_x = a->vec_y * b->vec_z - a->vec_z * b->vec_y;
	result->vec_y = a->vec_z * b->vec_x - a->vec_x * b->vec_z;
	result->vec_z = a->vec_x * b->vec_y - a->vec_y * b->vec_x;
	return (result);
}

t_vector	*normalize(t_vector *vector, t_garbage *gc)
{
	double		len;
	t_vector	*norm_vec;

	len = sqrt(vector->vec_x * vector->vec_x + vector->vec_y * vector->vec_y \
	+ vector->vec_z * vector->vec_z);
	norm_vec = (t_vector *) malloc(sizeof(t_vector));
	if (len == 0 && vector->vec_x == 0)
		norm_vec->vec_x = 0;
	else
		norm_vec->vec_x = vector->vec_x / len;
	if (len == 0 && vector->vec_y == 0)
		norm_vec->vec_y = 0;
	else
		norm_vec->vec_y = vector->vec_y / len;
	if (len == 0 && vector->vec_z == 0)
		norm_vec->vec_z = 0;
	else
		norm_vec->vec_z = vector->vec_z / len;
	norm_vec = get_vec(norm_vec->vec_x, norm_vec->vec_y, norm_vec->vec_z, gc);
	return (norm_vec);
}

t_vector	*vector_add(t_vector *vector, t_vector *help_vec, t_garbage *gc)
{
	t_vector	*new_vec;

	new_vec = get_vec(vector->vec_x + help_vec->vec_x, vector->vec_y + \
	help_vec->vec_y, vector->vec_z + help_vec->vec_z, gc);
	return (new_vec);
}

t_vector	*vector_sub(t_vector *v_height, t_vector *v_width, t_garbage *gc)
{
	t_vector	*new_vec;

	new_vec = get_vec(v_height->vec_x - v_width->vec_x, v_height->vec_y - \
	v_width->vec_y, v_height->vec_z - v_width->vec_z, gc);
	return (new_vec);
}

t_vector	*vector_mult(t_vector *vector, double mult, t_garbage *gc)
{
	t_vector	*new_vec;

	new_vec = get_vec(vector->vec_x * mult, vector->vec_y * mult, \
	vector->vec_z * mult, gc);
	return (new_vec);
}
