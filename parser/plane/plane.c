/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 16:08:42 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/12 20:57:28 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/minirt.h"

// // static void	print_struct(t_plane_rt *plane);
// static t_plane_rt	*find_1st(t_plane_rt *plane);
// static t_plane_rt	*find_last(t_plane_rt *plane);
// static void			append_node(t_plane_rt **plane, int id);


// int	parse_plane(char *line, t_main_rt *main_rt)
// {
// 	t_plane_rt	*plane;
// 	char		**split;

// 	plane = (t_plane_rt *)malloc(sizeof(t_plane_rt));
// 	if (!plane)
// 		return (ft_putendl_fd("Error: malloc error", 2), 1);
// 	plane->id = main_rt->plane_counter;
// 	main_rt->plane_counter++;
// 	split = ft_split(line, ' ');
// 	if (split[4] != NULL)
// 		return (ft_putendl_fd("Error: too many arguments", 2), 1);
// 	plane->coord = parse_coord(split[1]);
// 	plane->vec = parse_vec(split[2]);
// 	plane->color = parse_color(split[3]);
// 	plane->next = NULL;
// 	plane->prev = NULL;
// 	append_node(&plane, plane->id);
// 	main_rt->plane = find_1st(plane);
// 	ft_free(split);
// 	return (0);
// }

// static t_plane_rt	*find_1st(t_plane_rt *plane)
// {
// 	if (NULL == plane)
// 		return (NULL);
// 	while (plane->prev)
// 		plane = plane->prev;
// 	return (plane);
// }

// static t_plane_rt	*find_last(t_plane_rt *plane)
// {
// 	if (NULL == plane)
// 		return (NULL);
// 	while (plane->next)
// 		plane = plane->next;
// 	return (plane);
// }

// static void	append_node(t_plane_rt **plane, int id)
// {
// 	t_plane_rt	*node;
// 	t_plane_rt	*last_node;

// 	if (NULL == plane)
// 		return ;
// 	node = malloc(sizeof(t_plane_rt));
// 	if (NULL == node)
// 		return ;
// 	node->next = NULL;
// 	node->id = id;
// 	if (NULL == *plane)
// 	{
// 		*plane = node;
// 		node->prev = NULL;
// 	}
// 	else
// 	{
// 		last_node = find_last(*plane);
// 		last_node->next = node;
// 		node->prev = last_node;
// 	}
// }

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
