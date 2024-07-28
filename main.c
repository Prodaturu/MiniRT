/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:21:02 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/27 08:33:37 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minirt.h"

// @note
// free_rt_inits(rt) should be added at the start of free_all
// @note
// free_rt_inits(rt) should free all the rt specific allocations

t_main_rt	*main_rt_init(t_garbage *gc)
{
	t_main_rt	*main_rt;

	main_rt = (t_main_rt *)malloc(sizeof(t_main_rt));
	if (!main_rt)
		return (ft_putendl_fd("Error: malloc error", 2), exit(1), NULL);
	// main_rt->gc = gc;
	add_to_gc(gc, main_rt);
	return (main_rt);
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
		if (file_type)
			printf(RED "Provided: %s file, use .rt file\n" RESET, file_type);
		else
			printf(RED "File type not found, use .rt file\n" RESET);
		exit(1);
	}
	if (DEBUG)
		printf(GREEN "File type is: %s\n" RESET, file_type);
}

// int	main(int argc, char **argv)
// {
// 	t_garbage	*garb_col;
// 	t_main_rt	*main_rt;

// 	file_checker(argc, argv);
// 	garb_col = garbage_collector_init();
// 	main_rt = (t_main_rt *)malloc(sizeof(t_main_rt));
// 	if (!main_rt)
// 		return (ft_putendl_fd("Error: malloc error", 2), 1);
// 	main_rt_init(main_rt, garb_col);
// 	parser(garb_col, argv[1], main_rt);
// 	init_scene_struct(main_rt, garb_col);
// 	// printf("DEBUG!!\n");
// 	renderer(main_rt);
// 	free_garbage(garb_col);
// 	free(garb_col);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_garbage	*gc;
	t_main_rt	*rt;

	file_checker(argc, argv);
	gc = garbage_collector_init();
	rt = main_rt_init(gc);
	parser(argv[1], rt);
	free_garbage(gc);
	return (0);
}

// t_main_rt *open_and_init
// (int *fd, t_main_rt *main_rt, char **argv)
// {
// 	*fd = open(argv[1], O_RDONLY);
// 	main_rt = (t_main_rt *)malloc(sizeof(t_main_rt));
// 	if (!main_rt)
// 		return (ft_putendl_fd("Error: malloc error", 2),
//  close(*fd),
// 		(void *)0);
// 	if (*fd >= 0)
// 		main_rt_init(main_rt);
// 	else
// 		return (ft_putendl_fd("Error: file not found", 2),
// 	free(main_rt), (void *)0);
// 	return (main_rt);
// }

// int	main(int argc, char **argv)
// {
// 	int			fd;
// 	t_main_rt	*main_rt;

// 	main_rt = NULL;
// 	fd = 0;
// 	argument_check(argc, argv, main_rt, &fd);
// 	if (!parser(fd, main_rt))
// 		renderer(main_rt);
// 	else
// 		return (ft_putendl_fd("Error: parsing error", 2), 1);
// 	return (0);
// }

// /*
// to implement calculation colors in thread for each channel I need 
// how you want to calculate the color of the pixel (how you check inside
// the sphere, plane, cylinder, etc. if the ray intersects with the object)
// then I can build the logic when and how to change values in the image
// */
