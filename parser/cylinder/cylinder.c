/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:08:18 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/21 13:27:50 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void		append_node(t_cyl_rt **head, t_cyl_rt *cyl);
static t_cyl_rt	*find_last(t_cyl_rt *cyl);
int				parse_cylinder(char *line, t_parser *parser);
// static void	print_struct(t_cyl_rt *cyl);

int	parse_cylinder(char *line, t_parser *parser)
{
	t_cyl_rt	*cyl;
	char		**split;

	cyl = (t_cyl_rt *)malloc(sizeof(t_cyl_rt));
	if (!cyl)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	cyl->id = parser->cyl_counter;
	parser->cyl_counter++;
	split = ft_split(line, ' ');
	if (split[6] != NULL)
		return (ft_putendl_fd("Error: too many arguments", 2), 1);
	cyl->center = parse_coord(split[1], parser);
	cyl->vec = parse_vec(split[2], parser);
	cyl->diameter = ft_atod(split[3]);
	cyl->height = ft_atod(split[4]);
	cyl->color = parse_color(split[5], parser);
	cyl->next = NULL;
	cyl->prev = NULL;
	if (NULL == parser->cyl)
		parser->cyl = cyl;
	else
		append_node(&parser->cyl, cyl);
	ft_free(split);
	add_to_garb_col(parser->garbage_head, cyl);
	return (0);
}

static t_cyl_rt	*find_last(t_cyl_rt *cyl)
{
	if (NULL == cyl)
		return (NULL);
	while (cyl->next)
		cyl = cyl->next;
	return (cyl);
}

static void	append_node(t_cyl_rt **head, t_cyl_rt *new_node)
{
	t_cyl_rt	*last_node;

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

// print_struct(cyl);
// line above should be pasted before return (0) in parse_cylinder
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
