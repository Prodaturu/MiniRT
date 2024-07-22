/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:29:34 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/21 13:25:57 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// static void	print_struct(t_amb_rt *amb);

int	parse_ambient(char *line, t_parser *parser)
{
	char		**split;
	t_amb_rt	*amb;
	t_color_rt	*color;

	amb = (t_amb_rt *)malloc(sizeof(t_amb_rt));
	if (!amb)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	split = ft_split(line, ' ');
	color = parse_color(split[2], parser);
	if (split[3] != NULL)
		return (ft_putendl_fd("Error: to many arguments", 2), 1);
	parser->amb_counter++;
	amb->ratio = ft_atod(split[1]);
	amb->color = color;
	if (amb->ratio < 0 || amb->ratio > 1)
		return (ft_putendl_fd("Error: wrong ratio", 2), 1);
	parser->amb = amb;
	ft_free(split);
	add_to_garb_col(parser->garbage_head, amb);
	return (0);
}

// print_struct(parser->amb);
// static void	print_struct(t_amb_rt *amb)
// {
// 	printf("parser->amb->ratio: %f\n", amb->ratio);
// 	printf("parser->amb->color->r: %d\n", amb->color->r);
// 	printf("parser->amb->color->g: %d\n", amb->color->g);
// 	printf("parser->amb->color->b: %d\n", amb->color->b);
// }
