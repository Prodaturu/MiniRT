/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:29:34 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/03 21:20:13 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// static void	print_struct(t_amb_rt *amb);

int	parse_ambient(char *line, t_main_rt *main_rt)
{
	char		**split;
	t_amb_rt	*amb;
	t_color_rt	*color;

	amb = (t_amb_rt *)malloc(sizeof(t_amb_rt));
	if (!amb)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	split = ft_split(line, ' ');
	color = parse_color(split[2]);
	if (split[3] != NULL)
		return (ft_putendl_fd("Error: to many arguments", 2), 1);
	main_rt->amb_counter++;
	amb->ratio = ft_atod(split[1]);
	amb->color = color;
	if (amb->ratio < 0 || amb->ratio > 1)
		return (ft_putendl_fd("Error: wrong ratio", 2), 1);
	main_rt->amb = amb;
	ft_free(split);
	return (0);
}

// print_struct(main_rt->amb);
// static void	print_struct(t_amb_rt *amb)
// {
// 	printf("main_rt->amb->ratio: %f\n", amb->ratio);
// 	printf("main_rt->amb->color->r: %d\n", amb->color->r);
// 	printf("main_rt->amb->color->g: %d\n", amb->color->g);
// 	printf("main_rt->amb->color->b: %d\n", amb->color->b);
// }
