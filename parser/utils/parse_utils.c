/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:51:27 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/04 01:42:07 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_color_rt	*parse_color(char *str)
{
	t_color_rt	*color;
	char		**col;

	color = (t_color_rt *)malloc(sizeof(t_color_rt));
	if (!color)
		return (ft_putendl_fd("Error: malloc error", 2), (void *)0);
	col = ft_split(str, ',');
	color->r = ft_atoi(col[0]);
	color->g = ft_atoi(col[1]);
	color->b = ft_atoi(col[2]);
	ft_free(col);
	if (color->r < 0 || color->r > 255 || color->g < 0 || \
		color->g > 255 || color->b < 0 || color->b > 255)
		return (ft_putendl_fd("Error: wrong color", 2), (void *)0);
	return (color);
}

t_vec_rt	*parse_vec(char *str)
{
	t_vec_rt	*vec;
	char		**vec_coord;

	vec = (t_vec_rt *)malloc(sizeof(t_vec_rt));
	if (!vec)
		return (ft_putendl_fd("Error: malloc error", 2), (void *)0);
	vec_coord = ft_split(str, ',');
	vec->x = ft_atod(vec_coord[0]);
	vec->y = ft_atod(vec_coord[1]);
	vec->z = ft_atod(vec_coord[2]);
	ft_free(vec_coord);
	if (vec->x < -1 || vec->x > 1 || vec->y < -1 || \
		vec->y > 1 || vec->z < -1 || vec->z > 1)
		return (ft_putendl_fd("Error: wrong vector coordinates", 2), (void *)0);
	if ((vec->x * vec->x + vec->y * vec->y + vec->z * vec->z) > 1.05
		|| (vec->x * vec->x + vec->y * vec->y + vec->z * vec->z) < 0.95)
		return (ft_putendl_fd("Error: not a unit vector", 2), (void *)0);
	return (vec);
}

t_pov_rt	*parse_pov(char *str)
{
	t_pov_rt	*pov;
	char		**pov_coord;

	pov = (t_pov_rt *)malloc(sizeof(t_pov_rt));
	if (!pov)
		return (ft_putendl_fd("Error: malloc error", 2), (void *)0);
	pov_coord = ft_split(str, ',');
	pov->x = ft_atod(pov_coord[0]);
	pov->y = ft_atod(pov_coord[1]);
	pov->z = ft_atod(pov_coord[2]);
	ft_free(pov_coord);
	return (pov);
}

t_coord_rt	*parse_coord(char *str)
{
	t_coord_rt	*coord;
	char		**coord_coord;

	coord = (t_coord_rt *)malloc(sizeof(t_coord_rt));
	if (!coord)
		return (ft_putendl_fd("Error: malloc error", 2), (void *)0);
	coord_coord = ft_split(str, ',');
	coord->x = ft_atod(coord_coord[0]);
	coord->y = ft_atod(coord_coord[1]);
	coord->z = ft_atod(coord_coord[2]);
	ft_free(coord_coord);
	return (coord);
}
