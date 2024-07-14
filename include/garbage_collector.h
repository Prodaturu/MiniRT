/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:40:33 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/14 05:01:22 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include "../libft/include/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <string.h>
# include <math.h>

/**
 * @brief struct to store the garbage collector node
 * 
 * @param data pointer to the data to be stored
 * @param next pointer to the next node
 * @param prev pointer to the previous node
 */
typedef struct s_garb_node
{
	void				*ptr_data;
	struct s_garb_node	*next;
	struct s_garb_node	*prev;
}						t_garb_node;

/**
 * @brief struct to store the garbage collector data
 * 
 * @param length (size_t) : length of the garbage collector
 * @param head (t_garb_node) pointer to head node of garbage collector
 * @param tail (t_garb_node) pointer to tail node of garbage collector
 */
typedef struct s_garbage
{
	size_t			length;
	t_garb_node		*head;
	t_garb_node		*tail;
}					t_garbage;

//* --- --- --- garbage_remover.c --- --- --- *//

/**
 * @brief Removes a node from the garbage collector and assigns the
 * node to NULL to avoid double free
 * 
 * @param node pointer to the node to be removed
 * 
 * @note Helper function for free_garbage function
 */
void			free_node(t_garb_node *node);

/**
 * @brief Frees all the allocations that were requested to be handled by
 * the garbage collector.
 * After deleting all the nodes, the function proceeds to free the pointer
 * to the garbage collector itself, destroying the garbage collector.
 * So this function should be called at the end of the program.
 * 
 * @param garb_col pointer to the garbage collector
 * 
 * @note Called at end of program. Frees all allocations from 
 * garbage collector including the garbage collector itself
 */
void			free_garbage(t_garbage *garb_col);

/**
 * @brief Frees a specific node / allocation from the garbage collector
 *
 * This fuction is usefull when we need to free a specific node
 * after using it instead of keeping it in the garbage collector
 * till the end of program
 * 
 * @param garb_col pointer to the garbage collector
 * @param ptr pointer to the adress of the data to be freed
 */
void			free_specific_alloc(t_garbage *garb_col, void *ptr);

//* --- --- --- garbage_collector.c --- --- --- *//

/**
 * @brief Adds a new node that is to be handled by the garbage collector
 * 
 * @param garb_col pointer to the garbage collector instance
 * @param ptr pointer to the data to be stored
 */
void			add_to_garb_col(t_garbage *garb_col, void *ptr);

/**
 * @brief Displays all the allocations passed to the garbage 
 * collector in the order they were added
 * 
 * @param garb_col pointer to the garbage collector
 * @return int 0 if successful
 * 
 * @note This function is used for debugging purposes
 */
int				display_allocations(t_garbage *garb_col);

/**
 * @brief Initializes garbage collector. This function needs to be called
 * before any other function to be able to use the garbage collector.
 * sets the head, tail and length to NULL, NULL and 0 respectively.
 * 
 * @param garb_col pointer to the garbage collector
 * @param ptr pointer to the data to be stored
 * @return t_garb_node* pointer to nodes of the garbage collector
 *
 * @note Required to use "Garbage Collector"
 */
t_garbage		*garbage_collector_init(void);

#endif
