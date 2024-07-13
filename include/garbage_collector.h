/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 20:40:33 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/13 20:57:43 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

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
	void				*data;
	struct s_garb_node	*next;
	struct s_garb_node	*prev;
}			t_garb_node;

/**
 * @brief struct to store the garbage collector data
 * 
 * @param head pointer to the head of the garbage collector
 * @param tail pointer to the tail of the garbage collector
 * @param length length of the garbage collector
 */
typedef struct s_garbage
{
	t_garb_node		*head;
	t_garb_node		*tail;
	size_t			length;
}			t_garbage;

#endif