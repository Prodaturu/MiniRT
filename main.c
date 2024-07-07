/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:21:02 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/07 16:36:16 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minirt.h"

void	main_rt_init(t_main_rt *main_rt)
{
	main_rt->amb_counter = 0;
	main_rt->light_counter = 0;
	main_rt->cam_counter = 0;
	main_rt->sphere_counter = 0;
	main_rt->plane_counter = 0;
	main_rt->cyl_counter = 0;
}

t_main_rt	*open_and_init(int *fd, t_main_rt *main_rt, char **argv)
{
	*fd = open(argv[1], O_RDONLY);
	main_rt = (t_main_rt *)malloc(sizeof(t_main_rt));
	if (!main_rt)
		return (ft_putendl_fd("Error: malloc error", 2), close(*fd), \
		(void *)0);
	if (*fd >= 0)
		main_rt_init(main_rt);
	else
		return (ft_putendl_fd("Error: file not found", 2), \
		free(main_rt), (void *)0);
	return (main_rt);
}

void	argument_check(int argc, char **argv, t_main_rt *main_rt, int fd)
{
	if (argc != 2)
		return (ft_putendl_fd("Error: path to file expected", 2), 1);
	else if (ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", 3))
		return (ft_putendl_fd("Error: provide .rt file", 2), 1);
	else
		main_rt = open_and_init(&fd, main_rt, argv);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_main_rt	*main_rt;
	mlx_t		*mlx;

	main_rt = NULL;
	fd = 0;
	argument_check(argc, argv, main_rt, &fd);
	if (!parser(fd, main_rt))
		mlx = create_image(main_rt);
		// post_parsing(main_rt);
	else
		return (ft_putendl_fd("Error: parsing error", 2), 1);
	return (0);
}

/*
to implement calculation colors in thread for each channel I need 
how you want to calculate the color of the pixel (how you check inside
the sphere, plane, cylinder, etc. if the ray intersects with the object)
then I can build the logic when and how to change values in the image
*/
