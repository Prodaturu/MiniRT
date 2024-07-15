/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:06:29 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/14 23:52:00 by trosinsk         ###   ########.fr       */
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




typedef struct s_cam
{
	int				fov;
}		t_cam;

typedef struct s_world_rt
{
	int				objects_count;
}			t_world_rt;

#endif