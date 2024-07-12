/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 23:59:14 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/12 20:57:15 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// // static void	print_struct(t_main_rt *main_rt);

// int	parse_light(char *line, t_main_rt *main_rt)
// {
// 	char		**split;
// 	t_light_rt	*light;

// 	light = (t_light_rt *)malloc(sizeof(t_light_rt));
// 	if (!light)
// 		return (ft_putendl_fd("Error: malloc error", 2), 1);
// 	split = ft_split(line, ' ');
// 	if (split[4] != NULL)
// 		return (ft_putendl_fd("Error: too many arguments", 2), 1);
// 	main_rt->light_counter++;
// 	light->coord = parse_coord(split[1]);
// 	light->ratio = ft_atod(split[2]);
// 	if (light->ratio < 0 || light->ratio > 1)
// 		return (ft_putendl_fd("Error: wrong ratio", 2), 1);
// 	light->color = parse_color(split[3]);
// 	main_rt->light = light;
// 	ft_free(split);
// 	return (0);
// }
/*paste line below in line before return (0) in parse_light
print_struct(main_rt);
then uncoment function below
*/
/*static void	print_struct(t_main_rt *main_rt)
{
	printf("main_rt->light->coord->x: %f\n", main_rt->light->coord->x);
	printf("main_rt->light->coord->y: %f\n", main_rt->light->coord->y);
	printf("main_rt->light->coord->z: %f\n", main_rt->light->coord->z);
	printf("main_rt->light->color->r: %d\n", main_rt->light->color->r);
	printf("main_rt->light->color->g: %d\n", main_rt->light->color->g);
	printf("main_rt->light->color->b: %d\n", main_rt->light->color->b);
	printf("main_rt->light->ratio: %f\n", main_rt->light->ratio);
}*/
