/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:21:02 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/28 02:24:24 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//for every aim function 1st step-split line
//2nd step-check syntax
//3rd step-create struct
//4th step-create object, check how long is element, if have 3 or 4 elements
int	parse_line(char *line, t_main_rt *main_rt)
{
	if (line[0] == 'A' && line[1] == ' ')
		return (parse_ambient(line, main_rt));
	else if (line[0] == 'C' && line[1] == ' ')
		return (parse_camera(line, main_rt));
	else if (line[0] == 'L' && line[1] == ' ')
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
	t_main_rt	*main_rt;
	char		*line;

	main_rt = (t_main_rt *)malloc(sizeof(t_main_rt));
	line = get_next_line(fd);
	while (line)
	{
		if (parse_line(line, main_rt))
			line = get_next_line(fd);
		else
			return (ft_putendl_fd("Error: parsing error", 2), 1);
	}
	{
		//check syntax
		//create structs
		//create objects
		//render
		// close(fd);
	}
}

int	main(int argc, char **argv)
{
	int			fd;
	t_main_rt	*main_rt;

	if (argc != 2)
		return (ft_putendl_fd("Error: provide .rt file", 2), 1);
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", 3))
		return (ft_putendl_fd("Error: provide .rt file", 2), 1);
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (ft_putendl_fd("Error: file not found", 2), 1);
		else
			return (parser(fd, main_rt));
	}
	// create_image(main_rt); // to do
	// mlx_loop(main_rt->mlx->mlx);
	//do_your_math(main_rt); // to do
	// free_rt(main_rt);
	return (0);
}
