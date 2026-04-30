/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_remover.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 03:37:57 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/26 08:24:24 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/garbage_collector.h"

void	free_node(t_garb_node *node)
{
	if (!node)
		return ;
	free(node);
	node = NULL;
}

void	free_garbage(t_garbage *garb_col)
{
	t_garb_node	*current;
	t_garb_node	*next;

	if (garb_col->length == 0)
		return ;
	current = garb_col->tail;
	while (current)
	{
		garb_col->length--;
		if (current->ptr_data != NULL && current->ptr_data != garb_col)
			free_node(current->ptr_data);
		next = current;
		current = current->prev;
		free_node(next);
	}
	if (garb_col)
		free(garb_col);
	return ;
}
