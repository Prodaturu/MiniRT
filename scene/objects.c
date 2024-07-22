/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:34:38 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/22 02:14:12 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_objects	*objects_init(t_main_rt *main_rt, t_garbage *gc);
t_object	*obj_sphere(t_objects *objects, t_parser *parser, \
t_garbage *gc, int *id);
t_object	*obj_cylinder(t_objects *objects, t_parser *parser, \
t_garbage *gc, int *id);
t_object	*obj_plane(t_objects *objects, t_parser *parser, \
t_garbage *gc, int *id);

t_objects	*objects_init(t_main_rt *main_rt, t_garbage *gc)
{
	t_objects	*objects;
	t_object	*object;
	t_parser	*parser;
	int			id;

	objects = (t_objects *)malloc(sizeof(t_objects));
	if (objects == NULL)
		err_msg(gc, 1, "error allocating world\n", true);
	else
		add_to_garb_col(gc, objects);
	id = 0;
	main_rt->objects = objects;
	parser = main_rt->parser;
	while (parser->sphere != NULL)
		objects->object = obj_sphere(objects, parser, gc, &id);
	while (parser->plane != NULL)
		objects->object = obj_plane(objects, parser, gc, &id);
	while (parser->cyl != NULL)
		objects->object = obj_cylinder(objects, parser, gc, &id);
	object = objects->object;
	parser->objects = objects;
	objects->count = object->id;
	main_rt->scene->objects = objects;
	return (objects);
}

t_object	*obj_sphere(t_objects *objects, t_parser *parser, \
	t_garbage *gc, int *id)
{
	t_object	*object;

	object = (t_object *)malloc(sizeof(t_object));
	if (object == NULL)
		err_msg(gc, 1, "error allocating world\n", true);
	else
		add_to_garb_col(gc, object);
	object->id = *id;
	id++;
	object->type = SPHERE;
	objects->object = object;
	object->sphere = parser->sphere;
	add_to_garb_col(gc, object->sphere);
	parser->sphere = parser->sphere->next;
	return (object);
}

t_object	*obj_plane(t_objects *objects, t_parser *parser, \
	t_garbage *gc, int *id)
{
	t_object	*object;

	object = (t_object *)malloc(sizeof(t_object));
	if (object == NULL)
		err_msg(gc, 1, "error allocating world\n", true);
	else
		add_to_garb_col(gc, object);
	object->id = *id;
	id++;
	objects->object = object;
	object->type = PLANE;
	object->plane = parser->plane;
	add_to_garb_col(gc, object->plane);
	parser->plane = parser->plane->next;
	return (object);
}

t_object	*obj_cylinder(t_objects *objects, t_parser *parser, \
	t_garbage *gc, int *id)
{
	t_object	*object;

	object = (t_object *)malloc(sizeof(t_object));
	if (object == NULL)
		err_msg(gc, 1, "error allocating world\n", true);
	else
		add_to_garb_col(gc, object);
	object->id = *id;
	id++;
	object->type = CYLINDER;
	objects->object = object;
	object->cylinder = parser->cyl;
	add_to_garb_col(gc, object->cylinder);
	parser->cyl = parser->cyl->next;
	return (object);
}
