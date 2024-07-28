/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:37:37 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/26 10:24:00 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

// Allocate memory for new node
// Initialize new node
// handle the case when the garbage collector is empty (first call)
// handle the case when the garbage collector is not empty

void	add_to_gc(t_garbage *garb_col, void *ptr)
{
	t_garb_node	*new_node;

	if (!ptr)
		return ;
	new_node = malloc(sizeof(t_garb_node));
	if (!new_node)
		return (ft_putendl_fd("Error: Malloc Failure!", 2), exit(1));
	new_node->ptr_data = ptr;
	new_node->next = NULL;
	if (garb_col->length == 0)
	{
		new_node->prev = NULL;
		garb_col->length = 1;
		garb_col->head = new_node;
		garb_col->tail = new_node;
		return ;
	}
	new_node->prev = garb_col->tail;
	garb_col->tail->next = new_node;
	garb_col->tail = new_node;
	garb_col->length++;
	return ;
}

int	display_allocations(t_garbage *garb_col)
{
	t_garb_node	*current;
	int			index;

	index = -1;
	current = garb_col->head;
	printf("Current allocations:\n");
	while (current)
	{
		index++;
		printf("the pointer indexed %d points to : \"%p\"\n",
			index, current->ptr_data);
		current = current->next;
	}
	return (index);
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
