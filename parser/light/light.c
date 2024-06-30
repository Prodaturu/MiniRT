/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 23:59:14 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/30 00:36:20 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	print_struct(t_main_rt *main_rt)
{
	printf("main_rt->light->coord->x: %f\n", main_rt->light->coord->x);
	printf("main_rt->light->coord->y: %f\n", main_rt->light->coord->y);
	printf("main_rt->light->coord->z: %f\n", main_rt->light->coord->z);
	printf("main_rt->light->color->r: %d\n", main_rt->light->color->r);
	printf("main_rt->light->color->g: %d\n", main_rt->light->color->g);
	printf("main_rt->light->color->b: %d\n", main_rt->light->color->b);
	printf("main_rt->light->ratio: %f\n", main_rt->light->ratio);
}

int	parse_light(char *line, t_main_rt *main_rt)
{
	char		**split;
	char		**light_coord;
	char		**col;
	t_light_rt	*light;
	t_coord_rt	*coord;
	t_color_rt	*color;

	light = (t_light_rt *)malloc(sizeof(t_light_rt));
	if (!light)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	coord = (t_coord_rt *)malloc(sizeof(t_coord_rt));
	if (!coord)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	color = (t_color_rt *)malloc(sizeof(t_color_rt));
	if (!color)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	split = ft_split(line, ' ');
	if (split[4] != NULL)
		return (ft_putendl_fd("Error: too many arguments", 2), 1);
	main_rt->light_counter++;
	light_coord = ft_split(split[1], ',');
	coord->x = ft_atod(light_coord[0]);
	coord->y = ft_atod(light_coord[1]);
	coord->z = ft_atod(light_coord[2]);
	light->coord = coord;
	light->ratio = ft_atod(split[2]);
	if (light->ratio < 0 || light->ratio > 1)
		return (ft_putendl_fd("Error: wrong ratio", 2), 1);
	col = ft_split(split[3], ',');
	color->r = ft_atoi(col[0]);
	color->g = ft_atoi(col[1]);
	color->b = ft_atoi(col[2]);
	light->color = color;
	if (light->color->r < 0 || light->color->r > 255 || light->color->g < 0 || \
		light->color->g > 255 || light->color->b < 0 || light->color->b > 255)
		return (ft_putendl_fd("Error: wrong vector coordinates", 2), 1);
	main_rt->light = light;
	print_struct(main_rt);
	return (0);
}
	// print_struct(main_rt->light);



