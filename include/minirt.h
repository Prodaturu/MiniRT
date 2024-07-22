/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 01:29:10 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/21 01:08:07 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>
# include "../libft/include/libft.h"
# include "../gnl42/include/get_next_line.h"
# include "render_structs.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "garbage_collector.h"
# include "parser.h"

# define DEBUG 1
// # define DEBUG 0 // uncomment this line to disable debug mode

# define PI 3.14159265358979323846
# define WIDTH 1024
# define HEIGHT 768
# define YPSILON 0.000001

# define RESET "\x1B[0m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"

/**
 * @brief s_vec_rt struct to store object vectors
 * 
 * @param vc_x vector component in x direction
 * @param vc_y vector component in y direction
 * @param vc_z vector component in z direction
 */
typedef struct s_vector
{
	double			vec_x;
	double			vec_y;
	double			vec_z;
}				t_vector;

/**
 * @brief struct to store the scene data
 * 
 * @param sphere_count number of spheres in the scene
 * @param plane_count number of planes in the scene
 * @param cylinder_count number of cylinders in the scene
 */
typedef struct s_scene
{
	t_vector		*start_pixel;
	t_vector		*orientation;
	t_vector		*v_cam_canvas;
	t_vector		*v_width;
	t_vector		*v_height;
	t_vector		*pov;
	double			focal_length;
	double			pixel_width;
	double			pixel_height;
	double			half_width;
	double			half_height;
	double			fov;

}			t_scene;

/** 
 * @brief struct to store color data
 * 
 * @param red red color component
 * @param green green color component
 * @param blue blue color component
 * @param alpha alpha color component
 * @param rgb combined color
*/
typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
	int				rgb;
	int				alpha;
}				t_color;

// --- --- --- Main miniRT struct --- --- --- //

/**
 * @struct s_main_rt t_main_rt
 * @brief s_main_rt struct to store main miniRT data
 * 
 * @param sphere_counter sphere counter
 * @param plane_counter plane counter
 * @param cyl_counter cylinder counter
 * @param num_windows number of windows
 * @param img pointer to mlx_image_t struct
 * @param parser pointer to parser struct
 * @param garb_col pointer to garbage collector
 * @param vector pointer to vector struct
 * @param scene pointer to scene struct
 * @param color pointer to combined color
 */
typedef struct s_main_rt
{
	int				sphere_counter;
	int				plane_counter;
	int				cyl_counter;
	int				num_windows;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_parser		*parser;
	t_garbage		*garb_col;
	t_vector		*vector;
	t_scene			*scene;
	t_color			*color;
}				t_main_rt;

// --- --- --- main.c --- --- --- //

/**
 * @brief main function to run the program
 * 
 * @param argc number of arguments
 * @param argv arguments
 * @return int 
 * 
 * @details Main function to run the program
 * checks the syntax of the input file,
 * parses the objects in the scene,
 * updates the scene struct
 * draws the scene using the mlx library
 * and returns 0 if successful
 * and 1 if there is an error anywhere during execution
 */
int			main(int argc, char**argv);
void		main_rt_init(t_main_rt *main_rt, t_garbage *garb_col);

/**
 * @brief function to check the syntax of the input file
 * 
 * @param argc number of arguments
 * @param argv arguments
 */
void		file_checker(int argc, char **argv);

int			parser(t_garbage *g_c, char *f_n, t_main_rt *m_rt);
//build_scene
int			init_scene_struct(t_main_rt *main_rt, t_garbage *gc);
t_vector	*get_vec(double x, double y, double z, t_garbage *gc);

t_vector	*normalize(t_vector *vector, t_garbage *gc);
t_vector	*vector_add(t_vector *vector, t_vector *help_vec, t_garbage *gc);
t_vector	*vector_sub(t_vector *v_height, t_vector *v_width, t_garbage *gc);
t_vector	*vector_mult(t_vector *vector, double mult, t_garbage *gc);
t_vector	*cross(t_vector *a, t_vector *b, t_garbage *gc);
t_vector	*scalar_mult(t_vector *a, double c, t_garbage *gc);
t_vector	*set_orientation(t_vec_rt *orientation, t_garbage *gc);
t_vector	*set_pov(t_pov_rt *pov, t_garbage *gc);

//mlx
mlx_t		*renderer(t_main_rt *main_rt);


#endif