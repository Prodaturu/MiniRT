/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:08:42 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/20 17:38:16 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_plane_rt	*find_1st(t_plane_rt *plane);
static t_plane_rt	*find_last(t_plane_rt *plane);
static void			append_node(t_plane_rt **plane, int id);
// static void	print_struct(t_plane_rt *plane);

int	is_on_plane(t_vector coord, t_vector vec, t_vector point)
{
	if (vec.vec_x * (point.vec_x - coord.vec_x) + vec.vec_y * \
		(point.vec_y - coord.vec_y) + \
		vec.vec_z * (point.vec_z - coord.vec_z) == 0)
		return (1);
	return (0);
}

int	parse_plane(char *line, t_parser *parser)
{
	t_plane_rt	*plane;
	char		**split;

	plane = (t_plane_rt *)malloc(sizeof(t_plane_rt));
	if (!plane)
		return (ft_putendl_fd("Error: malloc error", 2), 1);
	plane->id = parser->plane_counter;
	parser->plane_counter++;
	split = ft_split(line, ' ');
	if (split[4] != NULL)
		return (ft_putendl_fd("Error: too many arguments", 2), 1);
	plane->coord = parse_coord(split[1]);
	plane->vec = parse_vec(split[2]);
	plane->color = parse_color(split[3]);
	plane->next = NULL;
	plane->prev = NULL;
	append_node(&plane, plane->id);
	parser->plane = find_1st(plane);
	ft_free(split);
	return (0);
}

static t_plane_rt	*find_1st(t_plane_rt *plane)
{
	if (NULL == plane)
		return (NULL);
	while (plane->prev)
		plane = plane->prev;
	return (plane);
}

static t_plane_rt	*find_last(t_plane_rt *plane)
{
	if (NULL == plane)
		return (NULL);
	while (plane->next)
		plane = plane->next;
	return (plane);
}

static void	append_node(t_plane_rt **plane, int id)
{
	t_plane_rt	*node;
	t_plane_rt	*last_node;

	if (NULL == plane)
		return ;
	node = malloc(sizeof(t_plane_rt));
	if (NULL == node)
		return ;
	node->next = NULL;
	node->id = id;
	if (NULL == *plane)
	{
		*plane = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last(*plane);
		last_node->next = node;
		node->prev = last_node;
	}
}

// print_struct(plane);
// static void	print_struct(t_plane_rt *plane)
// {
// 	printf("plane id: %d\n", plane->id);
// 	printf("plane coord: %f %f %f\n", plane->coord->x, plane->coord->y,
// 		plane->coord->z);
// 	printf("plane vector: %f %f %f\n", plane->vec->x, plane->vec->y,
// 		plane->vec->z);
// 	printf("plane color: %d %d %d\n", plane->color->r,
// 		plane->color->g, plane->color->b);
// }
