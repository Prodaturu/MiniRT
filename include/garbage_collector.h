/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:40:33 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/14 01:00:38 by sprodatu         ###   ########.fr       */
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

//* --- --- --- garbage_collector.c --- --- --- *//

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
 * @brief Initializes the first node of the garbage collector
 * and adds the pointer to the garbage collector
 * 
 * @param garb_col pointer to the garbage collector
 * @param ptr pointer to the data to be stored
 * @return t_garb_node* pointer to nodes of the garbage collector
 * 
 * @note This function needs to be called before any other to 
 * be able to use the garbage collector
 */
t_garbage		*garbage_collector_init(void);

#endif