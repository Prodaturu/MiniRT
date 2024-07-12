/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:06:29 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/12 21:18:10 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_STRUCTS_H
# define RENDER_STRUCTS_H

# include <stdbool.h>
# include <math.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_cam_rt
{
	int				fov;
}		t_cam_rt;

typedef struct s_world_rt
{
	int				objects_count;
}			t_world_rt;

#endif