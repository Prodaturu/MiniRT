/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 23:59:14 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/21 13:28:12 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// // static void	print_struct(t_parser *parser);

int	parse_light(char *line, t_parser *parser)
{
	char		**split;
	t_light_rt	*light;

	light = (t_light_rt *)malloc(sizeof(t_light_rt));
	if (!light)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	split = ft_split(line, ' ');
	if (split[4] != NULL)
		return (ft_putendl_fd("Error: too many arguments", 2), 1);
	parser->light_counter++;
	light->coord = parse_coord(split[1], parser);
	light->ratio = ft_atod(split[2]);
	if (light->ratio < 0 || light->ratio > 1)
		return (ft_putendl_fd("Error: wrong ratio", 2), 1);
	light->color = parse_color(split[3], parser);
	parser->light = light;
	ft_free(split);
	add_to_garb_col(parser->garbage_head, light);
	return (0);
}
/*paste line below in line before return (0) in parse_light
print_struct(parser);
then uncoment function below
*/
/*static void	print_struct(t_parser *parser)
{
	printf("parser->light->coord->x: %f\n", parser->light->coord->x);
	printf("parser->light->coord->y: %f\n", parser->light->coord->y);
	printf("parser->light->coord->z: %f\n", parser->light->coord->z);
	printf("parser->light->color->r: %d\n", parser->light->color->r);
	printf("parser->light->color->g: %d\n", parser->light->color->g);
	printf("parser->light->color->b: %d\n", parser->light->color->b);
	printf("parser->light->ratio: %f\n", parser->light->ratio);
}*/
