/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:31:08 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/13 19:27:26 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

// int	parse_line(char *line, t_main_rt *main_rt)
// {
// 	if (syntax_checker(line)) //done
// 		return (1);
// 	if (line[0] == 'A' && line[1] == ' ' && (main_rt->amb_counter < 1))
// 		return (parse_ambient(line, main_rt));
// 	else if (line[0] == 'C' && line[1] == ' ' && (main_rt->cam_counter < 1))
// 		return (parse_camera(line, main_rt));
// 	else if (line[0] == 'L' && line[1] == ' ' && (main_rt->light_counter < 1))
// 		return (parse_light(line, main_rt));
// 	else if (line[0] == 's' && line[1] == 'p')
// 		return (parse_sphere(line, main_rt));
// 	else if (line[0] == 'p' && line[1] == 'l')
// 		return (parse_plane(line, main_rt));
// 	else if (line[0] == 'c' && line[1] == 'y')
// 		return (parse_cylinder(line, main_rt));
// 	else
// 		return (0);
// }

int	err_msg(char *msg, int ret)
{
	ft_putendl_fd(msg, 2);
	if (ret)
		exit(ret);
	return (ret);
}

// int	parse_objects(t_scene_rt *scene)
// {
// }

int	parser(char	*file_name, t_scene_rt *scene)
{
	char		*line_read;
	int			fd;

	// if (!parse_objects(scene))
	// 	return (err_msg("Error: failed to parse objects", 1));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (err_msg("Error: failed to open file", 1));
	line_read = get_next_line(fd);
	while (line_read)
	{
		line_read = get_next_line(fd);
		if (line_read && line_read[0] != '\n')
		{
			if (line_read[ft_strlen(line_read) - 1] == '\n')
				line_read[ft_strlen(line_read) - 1] = '\0';
			// element_in(line_read, scene);
		}
	}
	// if (parse_check(scene))
	// 	return (err_msg("Error: failed to parse objects", 1));
	// else
	return (close(fd), 0);
}
// int	parser(int fd, t_main_rt *main_rt)
// {
// 	char		*line;

// 	line = get_next_line(fd);
// 	if (!line)
// 		return (ft_putendl_fd("Error: empty file", 2), 1);
// 	while (line)
// 	{
// 		if (!(parse_line(line, main_rt)))
// 			line = get_next_line(fd);
// 		else
// 			return (1);
// 	}
// 	close(fd);
// 	return (free(line), 0);
// }
