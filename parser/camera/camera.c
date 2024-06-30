/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:15:33 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/30 01:10:52 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	print_struct(t_main_rt *main_rt)
{
	printf("main_rt->cam->pov->x: %f\n", main_rt->cam->pov->x);
	printf("main_rt->cam->pov->y: %f\n", main_rt->cam->pov->y);
	printf("main_rt->cam->pov->z: %f\n", main_rt->cam->pov->z);
	printf("main_rt->cam->vec->x: %f\n", main_rt->cam->vec->x);
	printf("main_rt->cam->vec->y: %f\n", main_rt->cam->vec->y);
	printf("main_rt->cam->vec->z: %f\n", main_rt->cam->vec->z);
	printf("main_rt->cam->fov: %f\n", main_rt->cam->fov);
}

int	parse_camera(char *line, t_main_rt *main_rt)
{
	char		**split;
	char		**pov_coord;
	char		**vector;
	t_cam_rt	*cam;
	t_vec_rt	*vec;
	t_pov_rt	*pov;

	cam = (t_cam_rt *)malloc(sizeof(t_cam_rt));
	if (!cam)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	pov = (t_pov_rt *)malloc(sizeof(t_pov_rt));
	if (!pov)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	vec = (t_vec_rt *)malloc(sizeof(t_vec_rt));
	if (!vec)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	split = ft_split(line, ' ');
	if (split[4] != NULL)
		return (ft_putendl_fd("Error: too tooo too many arguments", 2), 1);
	main_rt->cam_counter++;
	pov_coord = ft_split(split[1], ',');
	pov->x = ft_atod(pov_coord[0]);
	pov->y = ft_atod(pov_coord[1]);
	pov->z = ft_atod(pov_coord[2]);
	cam->pov = pov;
	vector = ft_split(split[2], ',');
	vec->x = ft_atod(vector[0]);
	vec->y = ft_atod(vector[1]);
	vec->z = ft_atod(vector[2]);
	cam->vec = vec;
	cam->fov = ft_atoi(split[3]);
	if (cam->vec->x < -1 || cam->vec->x > 1 || cam->vec->y < -1 || \
		cam->vec->y > 1 || cam->vec->z < -1 || cam->vec->z > 1)
		return (ft_putendl_fd("Error: wrong vector coordinates", 2), 1);
	if (cam->fov < 0 || cam->fov > 180)
		return (ft_putendl_fd("Error: wrong fov", 2), 1);
	main_rt->cam = cam;
	print_struct(main_rt);
	return (0);
}
	// print_struct(main_rt->cam);



