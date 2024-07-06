/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 01:29:10 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/07 01:07:34 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/include/libft.h"
# include "../gnl42/include/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>

# define PI 3.14159265358979323846
# define WIDTH 1024
# define HEIGHT 768
# define VALID_SET "ACLsplcy +-.0123456789,\n"

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

// --- --- --- Geometry related structs --- --- --- //

typedef struct s_sphere_rt
{
	int					id;
	double				diameter;
	t_coord_rt			*center;
	t_color_rt			*color;
	struct s_sphere_rt	*next;
	struct s_sphere_rt	*prev;
}				t_sphere_rt;

typedef struct s_plane_rt
{
	int					id;
	t_coord_rt			*coord;
	t_vec_rt			*vec;
	t_color_rt			*color;
	struct s_plane_rt	*next;
	struct s_plane_rt	*prev;
}				t_plane_rt;

typedef struct s_cyl_rt
{
	int				id;
	double			diameter;
	double			height;
	t_coord_rt		*center;
	t_vec_rt		*vec;
	t_color_rt		*color;
	struct s_cyl_rt	*next;
	struct s_cyl_rt	*prev;
}				t_cyl_rt;

// --- --- --- Main miniRT struct --- --- --- //

typedef struct s_main_rt
{
	int				fd;
	int				amb_counter;
	int				cam_counter;
	int				light_counter;
	int				sphere_counter;
	int				plane_counter;
	int				cyl_counter;
	mlx_t			*mlx;
	t_amb_rt		*amb;
	t_cam_rt		*cam;
	t_light_rt		*light;
	t_sphere_rt		*sphere;
	t_plane_rt		*plane;
	t_cyl_rt		*cyl;
	t_color_rt		*color;
}				t_main_rt;

//ambient
int			parse_ambient(char *line, t_main_rt *main_rt);
//camera
int			parse_camera(char *line, t_main_rt *main_rt);
//light
int			parse_light(char *line, t_main_rt *main_rt);
//sphere
int			parse_sphere(char *line, t_main_rt *main_rt);
//plane
int			parse_plane(char *line, t_main_rt *main_rt);
//cylinder
int			parse_cylinder(char *line, t_main_rt *main_rt);
//parser
int			parse_line(char *line, t_main_rt *main_rt);
int			parser(int fd, t_main_rt *main_rt);
//parser/utils
double		ft_atod(char *str);
t_coord_rt	*parse_coord(char *str);
t_pov_rt	*parse_pov(char *str);
t_vec_rt	*parse_vec(char *str);
t_color_rt	*parse_color(char *str);
void		ft_free_all(t_main_rt *main_rt);
void		ft_free(char **str);
//mlx
mlx_t		*create_image(t_main_rt *main_rt);

#endif