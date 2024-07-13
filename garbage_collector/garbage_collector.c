/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:37:37 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/14 00:58:01 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

void	add_to_garb_col(t_garbage *garb_col, void *ptr)
{
	t_garb_node	*new_node;

	if (!ptr)
		return ;
	new_node = malloc(sizeof(t_garb_node));
	new_node->ptr_data = ptr;
	if (!new_node)
		return (ft_putendl_fd("Error: Malloc Failure!", 2), exit(1));
	if (garb_col->length == 0)
	{
		garb_col->length = 1;
		new_node->prev = NULL;
		new_node->next = NULL;
		garb_col->head = new_node;
		garb_col->tail = new_node;
		return ;
	}
	new_node->prev = garb_col->tail;
	new_node->next = NULL;
	garb_col->tail->next = new_node;
	garb_col->tail = new_node;
	garb_col->length++;
	return ;
}

void	free_specific_alloc(t_garbage *garb_col, void *ptr)
{
	t_garb_node	*current;
	t_garb_node	*prev;

	current = garb_col->head;
	while (current)
	{
		if (current->ptr_data == ptr)
		{
			free(current->ptr_data);
			if (prev == NULL)
				garb_col->head = current->next;
			else
				prev->next = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

int	display_allocations(t_garbage *garb_col)
{
	t_garb_node	*current;
	int			i;

	i = -1;
	current = garb_col->head;
	printf("Current allocations:\n");
	while (current)
	{
		i++;
		printf("the pointer at indexed %d points to : \"%p\"\n",
			i, current->ptr_data);
		current = current->next;
	}
	return (i);
}

t_garbage	*garbage_collector_init(void)
{
	t_garbage	*garb_col;

	garb_col = (t_garbage *)malloc(sizeof(t_garbage));
	if (!garb_col)
	{
		ft_putendl_fd("Error: garbage collector initialization failed", 2);
		exit(1);
	}
	garb_col->length = 0;
	garb_col->head = NULL;
	garb_col->tail = NULL;
	return (garb_col);
}
