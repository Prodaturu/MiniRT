/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 01:23:40 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/21 00:24:11 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int		err_msg(t_garbage *garb_col, int ex_flag, char *msg, int ret);
void	ft_free(char **str);
void	free_plane(t_plane_rt *plane);
void	free_cylinder(t_cyl_rt *cylinder);
void	free_sphere(t_sphere_rt *sphere);

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
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

void	free_plane(t_plane_rt *plane)
{
	t_plane_rt	*tmp;

	while (plane)
	{
		tmp = plane;
		plane = plane->next;
		free(tmp->coord);
		free(tmp->vec);
		free(tmp->color);
		free(tmp);
	}
}

void	free_sphere(t_sphere_rt *sphere)
{
	t_sphere_rt	*tmp;

	while (sphere)
	{
		tmp = sphere;
		sphere = sphere->next;
		free(tmp->center);
		free(tmp->color);
		free(tmp);
	}
}

void	free_cylinder(t_cyl_rt *cylinder)
{
	t_cyl_rt	*tmp;

	while (cylinder)
	{
		tmp = cylinder;
		cylinder = cylinder->next;
		free(tmp->center);
		free(tmp->vec);
		free(tmp->color);
		free(tmp);
	}
}
// void	ft_free_all(t_parser *parser)
// {
// 	if (parser->amb)
// 	{
// 		free(parser->amb->color);
// 		free(parser->amb);
// 	}
// 	if (parser->cam)
// 	{
// 		free(parser->cam->pov);
// 		free(parser->cam->orient_vec);
// 		free(parser->cam);
// 	}
// 	if (parser->light)
// 	{
// 		free(parser->light->coord);
// 		free(parser->light->color);
// 		free(parser->light);
// 	}
// 	if (parser->plane)
// 		free_plane(parser->plane);
// 	if (parser->sphere)
// 		free_sphere(parser->sphere);
// 	if (parser->cyl)
// 		free_cylinder(parser->cyl);
// 	free(parser);
// }
