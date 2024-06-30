/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 01:29:10 by trosinsk          #+#    #+#             */
/*   Updated: 2024/06/30 01:11:44 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/include/libft.h"
# include "../gnl42/include/get_next_line.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>

# define PI 3.14159265358979323846

typedef struct s_color_rt
{
	int				r;
	int				g;
	int				b;
}				t_color_rt;

typedef struct s_pov_rt
{
	double			x;
	double			y;
	double			z;
}				t_pov_rt;

typedef struct s_vec_rt
{
	double			x;
	double			y;
	double			z;
}				t_vec_rt;

typedef struct s_coord_rt
{
	double			x;
	double			y;
	double			z;
}				t_coord_rt;

typedef struct s_amb_rt
{
	double			ratio;
	t_color_rt		*color;
}				t_amb_rt;


typedef struct s_cam_rt
{
	t_pov_rt		*pov;
	t_vec_rt		*vec;
	double			fov;
}				t_cam_rt;

typedef struct s_light_rt
{
	t_coord_rt		*coord;
	double			ratio;
	t_color_rt		*color;
}				t_light_rt;

typedef struct s_sphere_rt
{
	t_coord_rt		*center;
	double			diameter;
	t_color_rt		*color;
}				t_sphere_rt;


typedef struct s_plane_rt
{
	t_coord_rt		*coord;
	t_vec_rt		*vec;
	t_color_rt		*color;
}				t_plane_rt;

typedef struct s_cylinder_rt
{
	t_coord_rt		*center;
	t_vec_rt		*vec;
	double			diameter;
	double			height;
	t_color_rt		*color;
}				t_cylinder_rt;

typedef struct s_main_rt
{
	int				res_x;
	int				res_y;
	int				fd;
	int				amb_counter;
	int				cam_counter;
	int				light_counter;
	int				sphere_counter;
	int				plane_counter;
	int				cylinder_counter;
	t_amb_rt		*amb;
	t_cam_rt		*cam;
	t_light_rt		*light;
	t_sphere_rt		*sphere;
	t_plane_rt		*plane;
	t_cylinder_rt	*cylinder;
	t_color_rt		*color;
}				t_main_rt;


//ambient
int		parse_ambient(char *line, t_main_rt *main_rt);
//camera
int		parse_camera(char *line, t_main_rt *main_rt);
//light
int		parse_light(char *line, t_main_rt *main_rt);
//sphere
int		parse_sphere(char *line, t_main_rt *main_rt);
//plane
int		parse_plane(char *line, t_main_rt *main_rt);
//cylinder
int		parse_cylinder(char *line, t_main_rt *main_rt);
//parser
int		parse_line(char *line, t_main_rt *main_rt);
int		parser(int fd, t_main_rt *main_rt);
//mlx
int		init_mlx(t_main_rt *main_rt);
//utils
double	ft_atod(char *str);
#endif