/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:49:07 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/20 17:38:21 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_sphere_rt	*find_1st(t_sphere_rt *sphere);
static t_sphere_rt	*find_last(t_sphere_rt *sphere);
static void			append_node(t_sphere_rt **sphere, int id);
int					parse_sphere(char *line, t_parser *parser);
// static void	print_struct(t_sphere_rt *sphere);

int	is_on_sphere(t_vector center, int diameter, t_vector point)
{
	if (sqrt(pow(point.vec_x - center.vec_x, 2) \
		+ pow(point.vec_y - center.vec_y, 2) + \
		pow(point.vec_z - center.vec_z, 2)) <= diameter / 2)
		return (1);
	return (0);
}

int	parse_sphere(char *line, t_parser *parser)
{
	t_sphere_rt	*sphere;
	char		**split;

	sphere = (t_sphere_rt *)malloc(sizeof(t_sphere_rt));
	if (!sphere)
		return (ft_putendl_fd("Error: malloc failed", 2), 1);
	sphere->id = parser->sphere_counter;
	parser->sphere_counter++;
	split = ft_split(line, ' ');
	if (split[4] != NULL)
		return (ft_putendl_fd("Error: to many arguments", 2), 1);
	sphere->center = parse_coord(split[1]);
	sphere->diameter = ft_atod(split[2]);
	sphere->color = parse_color(split[3]);
	sphere->next = NULL;
	sphere->prev = NULL;
	append_node(&sphere, sphere->id);
	parser->sphere = find_1st(sphere);
	ft_free(split);
	return (0);
}

static t_sphere_rt	*find_1st(t_sphere_rt *sphere)
{
	if (NULL == sphere)
		return (NULL);
	while (sphere->prev)
		sphere = sphere->prev;
	return (sphere);
}

static t_sphere_rt	*find_last(t_sphere_rt *sphere)
{
	if (NULL == sphere)
		return (NULL);
	while (sphere->next)
		sphere = sphere->next;
	return (sphere);
}

static void	append_node(t_sphere_rt **sphere, int id)
{
	t_sphere_rt	*node;
	t_sphere_rt	*last_node;

	if (NULL == sphere)
		return ;
	node = malloc(sizeof(t_sphere_rt));
	if (NULL == node)
		return ;
	node->next = NULL;
	node->id = id;
	if (NULL == *sphere)
	{
		*sphere = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last(*sphere);
		last_node->next = node;
		node->prev = last_node;
	}
}

// print_struct(sphere);
// static void	print_struct(t_sphere_rt *sphere)
// {
// 	printf("Sphere id: %d\n", sphere->id);
// 	printf("Sphere center: %f %f %f\n", sphere->center->x, sphere->center->y,
// 		sphere->center->z);
// 	printf("Sphere diameter: %f\n", sphere->diameter);
// 	printf("Sphere color: %d %d %d\n", sphere->color->r,
// 		sphere->color->g, sphere->color->b);
// }
