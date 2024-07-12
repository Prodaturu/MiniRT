/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:15:33 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/12 20:56:56 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// static void	print_struct(t_main_rt *main_rt);

// int	parse_camera(char *line, t_main_rt *main_rt)
// {
// 	char		**split;
// 	t_cam_rt	*cam;

// 	cam = (t_cam_rt *)malloc(sizeof(t_cam_rt));
// 	if (!cam)
// 		return (ft_putendl_fd("Error: malloc error", 2), 1);
// 	split = ft_split(line, ' ');
// 	if (split[1] == NULL || split[2] == NULL || split[3] == NULL)
// 		return (ft_putendl_fd("Error: not enough arguments", 2), 1);
// 	if (split[4] != NULL)
// 		return (ft_putendl_fd("Error: to many arguments", 2), 1);
// 	main_rt->cam_counter++;
// 	cam->pov = parse_pov(split[1]);
// 	cam->orient_vec = parse_vec(split[2]);
// 	cam->fov = ft_atoi(split[3]);
// 	if (cam->fov < 0 || cam->fov > 180)
// 		return (ft_putendl_fd("Error: wrong fov", 2), 1);
// 	cam->pixel_width = WIDTH;
// 	cam->pixel_height = HEIGHT;
// 	main_rt->cam = cam;
// 	ft_free(split);
// 	return (0);
// }
// print_struct(main_rt);
// static void	print_struct(t_main_rt *main_rt)
// {
// 	printf("main_rt->cam->pov->x: %f\n", main_rt->cam->pov->x);
// 	printf("main_rt->cam->pov->y: %f\n", main_rt->cam->pov->y);
// 	printf("main_rt->cam->pov->z: %f\n", main_rt->cam->pov->z);
// 	printf("main_rt->cam->vec->x: %f\n", main_rt->cam->vec->x);
// 	printf("main_rt->cam->vec->y: %f\n", main_rt->cam->vec->y);
// 	printf("main_rt->cam->vec->z: %f\n", main_rt->cam->vec->z);
// 	printf("main_rt->cam->fov: %f\n", main_rt->cam->fov);
// }
