/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 15:49:07 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/22 18:24:58 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_sphere_rt	*find_last(t_sphere_rt *sphere);
static void			append_node(t_sphere_rt **head, t_sphere_rt *new_node);
int					parse_sphere(char *line, t_parser *parser);
int					is_on_sphere(t_vector center, int diameter, t_vector point);
// static void	print_struct(t_sphere_rt *sphere);

int	is_on_sphere(t_vector center, int diameter, t_vector point)
{
	if (sqrt(pow(point.vec_x - center.vec_x, 2) \
		+ pow(point.vec_y - center.vec_y, 2) + \
		pow(point.vec_z - center.vec_z, 2)) <= diameter / 2)
		return (0);
	return (1);
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
	sphere->center = parse_coord(split[1], parser);
	sphere->diameter = ft_atod(split[2]);
	sphere->color = parse_color(split[3], parser);
	sphere->next = NULL;
	sphere->prev = NULL;
	if (NULL == parser->sphere)
		parser->sphere = sphere;
	else
		append_node(&parser->sphere, sphere);
	ft_free(split);
	add_to_garb_col(parser->garbage_head, sphere);
	return (0);
}

static t_sphere_rt	*find_last(t_sphere_rt *sphere)
{
	if (NULL == sphere)
		return (NULL);
	while (sphere->next)
		sphere = sphere->next;
	return (sphere);
}

static void	append_node(t_sphere_rt **head, t_sphere_rt *new_node)
{
	t_sphere_rt	*last_node;

	if (NULL == head || NULL == new_node)
		return ;
	if (NULL == *head)
		*head = new_node;
	else
	{
		last_node = find_last(*head);
		last_node->next = new_node;
		new_node->prev = last_node;
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
