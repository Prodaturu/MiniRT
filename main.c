/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:21:02 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/21 01:10:58 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minirt.h"

void	main_rt_init(t_main_rt *main_rt, t_garbage *garb_col);
void	file_checker(int argc, char **argv);

int	main(int argc, char **argv)
{
	t_garbage	*garb_col;
	t_main_rt	*main_rt;

	file_checker(argc, argv);
	garb_col = garbage_collector_init();
	main_rt = (t_main_rt *)malloc(sizeof(t_main_rt));
	if (!main_rt)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	main_rt_init(main_rt, garb_col);
	parser(garb_col, argv[1], main_rt);
	init_scene_struct(main_rt, garb_col);
// 	world_init(&world, &cam, &scene);
// 	renderer(&world, &cam, &scene);
	return (0);
}

void	main_rt_init(t_main_rt *main_rt, t_garbage *garb_col)
{
	main_rt->sphere_counter = 0;
	main_rt->plane_counter = 0;
	main_rt->cyl_counter = 0;
	main_rt->img = NULL;
	main_rt->color = NULL;
	add_to_garb_col(garb_col, main_rt);
}

void	file_checker(int argc, char **argv)
{
	char	*file_type;

	if (argc != 2)
	{
		ft_putendl_fd("Error: path to file expected", 2);
		exit(1);
	}
	file_type = ft_strrchr(argv[1], '.');
	if (!file_type || (ft_strncmp(file_type, ".rt", 3) != 0)
		|| (ft_strlen(file_type) != 3))
	{
		ft_putendl_fd("Error: provide a .rt file", 2);
		printf(RED "provided: %s file, use .rt file\n" RESET, file_type);
		exit(1);
	}
	if (DEBUG)
		printf(GREEN "File type is: %s\n" RESET, file_type);
}
