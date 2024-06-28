/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 01:29:10 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/28 02:12:31 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "./libft/include/libft.h"
# include "./gnl42/include/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>

# define PI 3.14159265358979323846

typedef struct main_rt
{
	int				res_x;
	int				res_y;
	int				fd;
	t_mlx			*mlx;
	t_amb_rt		*amb;
	t_cam_rt		*cam;
	t_light_rt		*light;
	t_sphere_rt		*sphere;
	t_plane_rt		*plane;
	t_cylinder_rt	*cylinder;
	t_color_rt		*color;
}				t_main_rt;

typedef struct amb_rt
{
	int				counter;
	double			ratio;
	t_color_rt		*color;
}				t_amb_rt;

typedef struct cam_rt
{
	int				counter;
	t_pov_rt		*pov;
	t_vec_rt		*vec;
	double			fov;
}				t_cam_rt;

typedef struct light_rt
{
	int				counter;
	t_coord_rt		*coord;
	double			ratio;
	t_color_rt		*color;
}				t_light_rt;

typedef struct sphere_rt
{
	t_center_rt		*center;
	double			diameter;
	t_color_rt		*color;
}				t_sphere_rt;


typedef struct plane_rt
{
	t_coord_rt		*coord;
	t_vec_rt		*vec;
	t_color_rt		*color;
}				t_plane_rt;

typedef struct cylinder_rt
{
	t_center_rt		*center;
	t_vec_rt		*vec;
	double			diameter;
	double			height;
	t_color_rt		*color;
}				t_cylinder_rt;
#endif