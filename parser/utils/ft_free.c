/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 01:23:40 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/01 01:53:29 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	ft_free_all(t_main_rt *main_rt);
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

void	ft_free_all(t_main_rt *main_rt)
{
	if (main_rt->amb)
	{
		free(main_rt->amb->color);
		free(main_rt->amb);
	}
	if (main_rt->cam)
	{
		free(main_rt->cam->pov);
		free(main_rt->cam->vec);
		free(main_rt->cam);
	}
	if (main_rt->light)
	{
		free(main_rt->light->coord);
		free(main_rt->light->color);
		free(main_rt->light);
	}
	if (main_rt->plane)
		free_plane(main_rt->plane);
	if (main_rt->sphere)
		free_sphere(main_rt->sphere);
	if (main_rt->cyl)
		free_cylinder(main_rt->cyl);
	free(main_rt);
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
