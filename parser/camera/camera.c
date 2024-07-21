/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 20:15:33 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/21 13:26:44 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// static void	print_struct(t_parser *parser);

int	parse_camera(char *line, t_parser *parser)
{
	char		**split;
	t_cam_rt	*cam;

	cam = (t_cam_rt *)malloc(sizeof(t_cam_rt));
	if (!cam)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	split = ft_split(line, ' ');
	if (split[1] == NULL || split[2] == NULL || split[3] == NULL)
		return (ft_putendl_fd("Error: not enough arguments", 2), 1);
	if (split[4] != NULL)
		return (ft_putendl_fd("Error: to many arguments", 2), 1);
	parser->cam_counter++;
	cam->pov = parse_pov(split[1], parser);
	cam->orient_vec = parse_vec(split[2], parser);
	cam->fov = ft_atoi(split[3]);
	if (cam->fov < 0 || cam->fov > 180)
		return (ft_putendl_fd("Error: wrong fov", 2), 1);
	parser->cam = cam;
	ft_free(split);
	add_to_garb_col(parser->garbage_head, cam);
	return (0);
}
// print_struct(parser);
// static void	print_struct(t_parser *parser)
// {
// 	printf("parser->cam->pov->pv_x : %f\n", parser->cam->pov->pv_x );
// 	printf("parser->cam->pov->pv_y: %f\n", parser->cam->pov->pv_y);
// 	printf("parser->cam->pov->pv_z: %f\n", parser->cam->pov->pv_z);
// 	printf("parser->cam->vec->x: %f\n", parser->cam->vec->x);
// 	printf("parser->cam->vec->y: %f\n", parser->cam->vec->y);
// 	printf("parser->cam->vec->z: %f\n", parser->cam->vec->z);
// 	printf("parser->cam->fov: %f\n", parser->cam->fov);
// }
