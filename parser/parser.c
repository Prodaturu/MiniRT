/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:31:08 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/20 17:54:37 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"


int			parse_line(char *line, t_parser *parser);
int			checker(char *line);
t_parser	*parse_init(t_main_rt *main_rt, t_garbage *garb_col);

int	parser(t_garbage *garb_col, char *file_n, t_main_rt *m)
{
	int			fd;
	char		*line_read;
	t_parser	*parser;

	if (!garb_col || !file_n)
		return (err_msg(garb_col, 1, "Error: invalid arguments", 1), 1);
	fd = open(file_n, O_RDONLY);
	if (fd < 0)
		return (err_msg(garb_col, 1, "Error: failed to open file", 1), 1);
	parser = parse_init(m, garb_col);
	line_read = get_next_line(fd);
	while (line_read)
	{
		if (!parse_line(line_read, parser))
			line_read = get_next_line(fd);
		else
			return (err_msg(garb_col, 1, "Error: failed to parse line", 1), 1);
	}
	return (close(fd), free(line_read), 0);
}

t_parser	*parse_init(t_main_rt *main_rt, t_garbage *garb_col)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (!parser)
		return (ft_putendl_fd("Error: malloc error", 2), (void *)0);
	parser->amb_counter = 0;
	parser->cam_counter = 0;
	parser->light_counter = 0;
	parser->sphere_counter = 0;
	parser->plane_counter = 0;
	parser->cyl_counter = 0;
	parser->amb = NULL;
	parser->cam = NULL;
	parser->light = NULL;
	parser->sphere = NULL;
	parser->plane = NULL;
	parser->cyl = NULL;
	parser->color = NULL;
	main_rt->parser = parser;
	add_to_garb_col(garb_col, parser);
	return (parser);
}

int	parse_line(char *line, t_parser *parser)
{
	if (checker(line))
		return (1);
	if (line[0] == 'A' && line[1] == ' ' && (parser->amb_counter < 1))
		return (parse_ambient(line, parser));
	else if (line[0] == 'C' && line[1] == ' ' && (parser->cam_counter < 1))
		return (parse_camera(line, parser));
	else if (line[0] == 'L' && line[1] == ' ' && (parser->light_counter < 1))
		return (parse_light(line, parser));
	else if (line[0] == 's' && line[1] == 'p')
		return (parse_sphere(line, parser));
	else if (line[0] == 'p' && line[1] == 'l')
		return (parse_plane(line, parser));
	else if (line[0] == 'c' && line[1] == 'y')
		return (parse_cylinder(line, parser));
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
