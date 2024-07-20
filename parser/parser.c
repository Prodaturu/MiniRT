/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:31:08 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/16 06:27:19 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	parse_line(char *line, t_main_rt *main_rt);
int	init_scene_struct(t_scene_rt *scene);
int	err_msg(t_garbage *garb_col, int ex_flag, char *msg, int ret);
int	parser(t_garbage *garb_col, char *file_n, t_scene_rt *scene, t_main_rt *m);
int	checker(char *line);

int	init_scene_struct(t_scene_rt *scene)
{
	scene = malloc(sizeof(t_scene_rt));
	if (!scene)
		return (1);
	scene->cylinder_count = 0;
	scene->plane_count = 0;
	scene->sphere_count = 0;
	return (1);
}

int	err_msg(t_garbage *garb_col, int ex_flag, char *msg, int ret)
{
	(void)ex_flag;
	if (!msg)
		return (ret);
	printf("%s\n", msg);
	free_garbage(garb_col);
	exit(ret);
	return (ret);
}

int	parser(t_garbage *garb_col, char *file_n, t_scene_rt *scene, t_main_rt *m)
{
	int			fd;
	char		*line_read;

	if (!garb_col || !file_n || !scene)
		return (err_msg(garb_col, 1, "Error: invalid arguments", 1), 1);
	if (!init_scene_struct(scene))
		return (err_msg(garb_col, 1, "Error: failed to init scene", 1), 1);
	fd = open(file_n, O_RDONLY);
	if (fd < 0)
		return (err_msg(garb_col, 1, "Error: failed to open file", 1), 1);
	main_rt_init(m);
	line_read = get_next_line(fd);
	while (line_read)
	{
		if (!parse_line(line_read, m))
			line_read = get_next_line(fd);
		else
			return (err_msg(garb_col, 1, "Error: failed to parse line", 1), 1);
	}
	return (close(fd), free(line_read), 0);
}

int	parse_line(char *line, t_main_rt *main_rt)
{
	if (checker(line))
		return (1);
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

int	checker(char *line)
{
	if (!line)
		return (1);
	if (line[0] == '\0')
		return (1);
	while (*line)
	{
		if (!ft_isdigit(*line) && !ft_strchr(VALID_SET, *line))
			return (1);
		line++;
	}
	return (0);
}
