/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 23:34:38 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/23 03:04:00 by trosinsk         ###   ########.fr       */
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

// t_objects	*objects_init(t_main_rt *main_rt, t_garbage *gc)
// {
// 	t_objects	*objects;
// 	t_object	*object;
// 	t_parser	*parser;
// 	int			id;

// 	objects = (t_objects *)malloc(sizeof(t_objects));
// 	if (objects == NULL)
// 		err_msg(gc, 1, "error allocating world\n", true);
// 	else
// 		add_to_garb_col(gc, objects);
// 	id = 0;
// 	main_rt->objects = objects;
// 	parser = main_rt->parser;
// 	while (parser->sphere != NULL)
// 	{
// 		objects->object = obj_sphere(objects, parser, gc, &id);
// 		parser->sphere = parser->sphere->next;
// 	}
// 	while (parser->plane != NULL)
// 	{
// 		objects->object = obj_plane(objects, parser, gc, &id);
// 		parser->plane = parser->plane->next;
// 	}
// 	while (parser->cyl != NULL)
// 	{
// 		objects->object = obj_cylinder(objects, parser, gc, &id);
// 		parser->cyl = parser->cyl->next;
// 	}
// 	object = objects->object;
// 	parser->objects = objects;
// 	objects->count = object->id;
// 	printf("objects count: %d\n", objects->count);
// 	printf("object id: %d\n", object->id);
// 	main_rt->scene->objects = objects;
// 	return (objects);
// }

t_objects	*objects_init(t_main_rt *main_rt, t_garbage *gc)
{
	t_objects	*objects;
	t_object	*last_object;
	t_parser	*parser;
	int			id;

	objects = (t_objects *)malloc(sizeof(t_objects));
	if (objects == NULL)
		err_msg(gc, 1, "error allocating world\n", true);
	else
		add_to_garb_col(gc, objects);
	id = 0;
	objects->object = NULL;
	parser = main_rt->parser;
	while (parser->sphere || parser->plane || parser->cyl)
	{
		if (parser->sphere)
		{
			if (!objects->object)
			{
				objects->object = obj_sphere(objects, parser, gc, &id);
				last_object = objects->object;
			}
			else
			{
				objects->object = obj_sphere(objects, parser, gc, &id);
				last_object = last_object->next;
			}
			parser->sphere = parser->sphere->next;
		}
		if (parser->plane)
		{
			if (!objects->object)
			{
				objects->object = obj_plane(objects, parser, gc, &id);
				last_object = objects->object;
			}
			else
			{
				objects->object = obj_plane(objects, parser, gc, &id);
				last_object = last_object->next;
			}
			parser->plane = parser->plane->next;
		}
		if (parser->cyl)
		{
			if (!objects->object)
			{
				objects->object = obj_cylinder(objects, parser, gc, &id);
				last_object = objects->object;
			}
			else
			{
				objects->object = obj_cylinder(objects, parser, gc, &id);
				last_object = last_object->next;
			}
			parser->cyl = parser->cyl->next;
		}
	}
	objects->count = id;
	printf("objects count: %d\n", objects->count);
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
	printf("id    sphere: %d\n", *id);
	printf("id%d\n", *id);
	(*id)++;
	object->type = SPHERE;
	objects->object = object;
	object->sphere = parser->sphere;
	object->color = parser->sphere->color;
	add_to_garb_col(gc, object->sphere);
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
	printf("id    plane: %d\n", *id);
	printf("id%d\n", *id);
	(*id)++;
	objects->object = object;
	object->type = PLANE;
	object->plane = parser->plane;
	object->color = parser->plane->color;
	add_to_garb_col(gc, object->plane);
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
	printf("id    cylinder: %d\n", *id);
	printf("id%d\n", *id);
	(*id)++;
	object->type = CYLINDER;
	objects->object = object;
	object->cylinder = parser->cyl;
	object->color = parser->cyl->color;
	add_to_garb_col(gc, object->cylinder);
	return (object);
}
