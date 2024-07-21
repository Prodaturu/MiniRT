/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:51:27 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/21 13:24:25 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_color_rt	*parse_color(char *str, t_parser *parser)
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
	add_to_garb_col(parser->garbage_head, color);
	return (color);
}

t_vec_rt	*parse_vec(char *str, t_parser *parser)
{
	t_vec_rt	*vec;
	char		**vec_coord;

	vec = (t_vec_rt *)malloc(sizeof(t_vec_rt));
	if (!vec)
		return (ft_putendl_fd("Error: malloc error", 2), (void *)0);
	vec_coord = ft_split(str, ',');
	vec->vc_x = ft_atod(vec_coord[0]);
	vec->vc_y = ft_atod(vec_coord[1]);
	vec->vc_z = ft_atod(vec_coord[2]);
	ft_free(vec_coord);
	if (vec->vc_x < -1 || vec->vc_x > 1 || vec->vc_y < -1 || \
		vec->vc_y > 1 || vec->vc_z < -1 || vec->vc_z > 1)
		return (ft_putendl_fd("Error: wrong vector coordinates", 2), (void *)0);
	if ((vec->vc_x * vec->vc_x + vec->vc_y * vec->vc_y + \
		vec->vc_z * vec->vc_z) > 1.05 || (vec->vc_x * vec->vc_x + \
		vec->vc_y * vec->vc_y + vec->vc_z * vec->vc_z) < 0.95)
		return (ft_putendl_fd("Error: not a unit vector", 2), (void *)0);
	add_to_garb_col(parser->garbage_head, vec);
	return (vec);
}

t_pov_rt	*parse_pov(char *str, t_parser *parser)
{
	t_pov_rt	*pov;
	char		**pov_coord;

	pov = (t_pov_rt *)malloc(sizeof(t_pov_rt));
	if (!pov)
		return (ft_putendl_fd("Error: malloc error", 2), (void *)0);
	pov_coord = ft_split(str, ',');
	pov->pv_x = ft_atod(pov_coord[0]);
	pov->pv_y = ft_atod(pov_coord[1]);
	pov->pv_z = ft_atod(pov_coord[2]);
	ft_free(pov_coord);
	add_to_garb_col(parser->garbage_head, pov);
	return (pov);
}

t_coord_rt	*parse_coord(char *str, t_parser *parser)
{
	t_coord_rt	*coord;
	char		**coord_coord;

	coord = (t_coord_rt *)malloc(sizeof(t_coord_rt));
	if (!coord)
		return (ft_putendl_fd("Error: malloc error", 2), (void *)0);
	coord_coord = ft_split(str, ',');
	coord->co_x = ft_atod(coord_coord[0]);
	coord->co_y = ft_atod(coord_coord[1]);
	coord->co_z = ft_atod(coord_coord[2]);
	ft_free(coord_coord);
	add_to_garb_col(parser->garbage_head, coord);
	return (coord);
}
