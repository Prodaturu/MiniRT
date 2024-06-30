/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:08:18 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/01 00:26:48 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

// static void	print_struct(t_cyl_rt *cyl)
// {
// 	printf("Cylinder id: %d\n", cyl->id);
// 	printf("Cylinder center: %f %f %f\n", cyl->center->x,
//	cyl->center->y,	cyl->center->z);
// 	printf("Cylinder vector: %f %f %f\n", cyl->vec->x, cyl->vec->y,
// 		cyl->vec->z);
// 	printf("Cylinder diameter: %f\n", cyl->diameter);
// 	printf("Cylinder height: %f\n", cyl->height);
// 	printf("Cylinder color: %d %d %d\n", cyl->color->r,
// 		cyl->color->g, cyl->color->b);
// }

static t_cyl_rt	*find_1st(t_cyl_rt *cyl)
{
	if (NULL == cyl)
		return (NULL);
	while (cyl->prev)
		cyl = cyl->prev;
	return (cyl);
}

static t_cyl_rt	*find_last(t_cyl_rt *cyl)
{
	if (NULL == cyl)
		return (NULL);
	while (cyl->next)
		cyl = cyl->next;
	return (cyl);
}

static void	append_node(t_cyl_rt **cyl, int id)
{
	t_cyl_rt	*node;
	t_cyl_rt	*last_node;

	if (NULL == cyl)
		return ;
	node = malloc(sizeof(t_cyl_rt));
	if (NULL == node)
		return ;
	node->next = NULL;
	node->id = id;
	if (NULL == *cyl)
	{
		*cyl = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last(*cyl);
		last_node->next = node;
		node->prev = last_node;
	}
}

int	parse_cylinder(char *line, t_main_rt *main_rt)
{
	t_cyl_rt	*cyl;
	char		**split;

	cyl = (t_cyl_rt *)malloc(sizeof(t_cyl_rt));
	if (!cyl)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	cyl->id = main_rt->cyl_counter;
	main_rt->cyl_counter++;
	split = ft_split(line, ' ');
	if (split[6] != NULL)
		return (ft_putendl_fd("Error: too many arguments", 2), 1);
	cyl->center = parse_coord(split[1]);
	cyl->vec = parse_vec(split[2]);
	cyl->diameter = ft_atod(split[3]);
	cyl->height = ft_atod(split[4]);
	cyl->color = parse_color(split[5]);
	cyl->next = NULL;
	cyl->prev = NULL;
	append_node(&cyl, cyl->id);
	main_rt->cyl = find_1st(cyl);
	return (0);
}
	// print_struct(cyl);
