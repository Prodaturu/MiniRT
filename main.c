/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:21:02 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/30 18:34:25 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minirt.h"

	// main_rt->mlx = (t_mlx_rt *)malloc(sizeof(t_mlx_rt));
	// main_rt->mlx->mlx = mlx_init();
	// main_rt->mlx->win = mlx_new_window(main_rt->mlx->mlx, 
	//1920, 1080, "miniRT");
	// main_rt->amb = (t_amb_rt *)malloc(sizeof(t_amb_rt));
	// main_rt->light = (t_light_rt *)malloc(sizeof(t_light_rt));
	// main_rt->cam = (t_cam_rt *)malloc(sizeof(t_cam_rt));
void	main_rt_init(t_main_rt *main_rt)
{
	main_rt->amb_counter = 0;
	main_rt->light_counter = 0;
	main_rt->cam_counter = 0;
	main_rt->sphere_counter = 0;
	main_rt->plane_counter = 0;
	main_rt->cyl_counter = 0;
}


int	main(int argc, char **argv)
{
	int			fd;
	t_main_rt	*main_rt;

	main_rt = NULL;
	if (argc != 2)
		return (ft_putendl_fd("Error: path to file expected", 2), 1);
	else if (ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", 3))
		return (ft_putendl_fd("Error: provide .rt file", 2), 1);
	else
	{
		fd = open(argv[1], O_RDONLY);
		main_rt = (t_main_rt *)malloc(sizeof(t_main_rt));
		if (!main_rt)
			return (ft_putendl_fd("Error: malloc error", 2), close(fd), 1);
		main_rt_init(main_rt);
		if (fd < 0)
			return (ft_putendl_fd("Error: file not found", 2), 1);
		else
		{
			printf("fd: %d\n", fd);
			return (parser(fd, main_rt));
		}
	}
	return (0);
}
	// create_image(main_rt); // to do
	// mlx_loop(main_rt->mlx->mlx);
	//do_your_math(main_rt); // to do
	// free_rt(main_rt);
