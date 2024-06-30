/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:31:08 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/01 00:32:43 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	parse_line(char *line, t_main_rt *main_rt)
{
	if (line[0] == 'A' && line[1] == ' ' && (main_rt->amb_counter < 1))
		return (parse_ambient(line, main_rt));
	else if (line[0] == 'C' && line[1] == ' ' && (main_rt->cam_counter < 1))
		return (parse_camera(line, main_rt));
	else if (line[0] == 'L' && line[1] == ' ' && (main_rt->light_counter < 1))
		return (parse_light(line, main_rt));
	else if (line[0] == 's' && line[1] == 'p')
		return (parse_sphere(line, main_rt));
	else if (line[0] == 'p' && line[1] == 'l')
		return (parse_plane(line, main_rt));
	else if (line[0] == 'c' && line[1] == 'y')
		return (parse_cylinder(line, main_rt));
	else
		return (0);
}

int	parser(int fd, t_main_rt *main_rt)
{
	char		*line;

	line = get_next_line(fd);
	if (!line)
		return (ft_putendl_fd("Error: empty file", 2), 1);
	while (line)
	{
		if (!(parse_line(line, main_rt)))
			line = get_next_line(fd);
		else
			return (ft_putendl_fd("Error: parsing error", 2), 1);
	}
	close(fd);
	return (free(line), 0);
}
