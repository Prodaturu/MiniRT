/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 01:29:10 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/15 01:22:18 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/include/libft.h"
# include "../gnl42/include/get_next_line.h"
# include "./render_structs.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "./garbage_collector.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>

# define DEBUG 1
// # define DEBUG 0 // uncomment this line to disable debug mode

# define PI 3.14159265358979323846
# define WIDTH 1024
# define HEIGHT 768

# define VALID_SET "ACLsplcy +-.0123456789,\n"

# define RESET "\x1B[0m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"

/**
 * @brief struct to store the scene data
 * 
 * @param sphere_count number of spheres in the scene
 * @param plane_count number of planes in the scene
 * @param cylinder_count number of cylinders in the scene
 */
typedef struct s_scene_rt
{
	int					sphere_count;
	int					plane_count;
	int					cylinder_count;
}			t_scene_rt;

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
/**
 * @brief function to check the syntax of the input file
 * 
 * @param argc number of arguments
 * @param argv arguments
 */
void		syntax_checker(int argc, char **argv);

// --- --- --- parser.c --- --- --- //

/**
 * @brief function to parse the objects in the scene
 * 
 * @param file_name name of the file to parse
 * @param scene pointer to the scene struct
 * 
 * @details This function will parse the objects
 * in the scene and update the scene struct
 */
// int				parser(char	*file_name, t_scene_rt *scene);

typedef struct s_color_rt
{
	int				r;
	int				g;
	int				b;
}				t_color_rt;

/**
 * @brief s_pov_rt struct to store point of view coordinates
 * 
 * @param x point of view x coordinate
 * @param y point of view y coordinate
 * @param z point of view z coordinate
 */

typedef struct s_coord_rt
{
	double			co_x;
	double			co_y;
	double			co_z;
}				t_coord_rt;

/**
 * @brief s_vec_rt struct to store object vectors
 * 
 * @param vc_x vector component in x direction
 * @param vc_y vector component in y direction
 * @param vc_z vector component in z direction
 */
typedef struct s_vec_rt
{
	double			vc_x;
	double			vc_y;
	double			vc_z;
}				t_vec_rt;

/**
 * @brief s_coord_rt struct to store object coordinates
 * 
 * @param pv_x x coordinate
 * @param pv_y y coordinate
 * @param pv_z z coordinate
 */
typedef struct s_pov_rt
{
	double			pv_x;
	double			pv_y;
	double			pv_z;
}				t_pov_rt;

/**
 * @brief s_amb_rt struct to store ambient light data
 * 
 * @param ratio ambient light ratio
 * @param color pointer to ambient light color
 */

typedef struct s_amb_rt
{
	double			ratio;
	t_color_rt		*color;
}				t_amb_rt;

/**
 * @brief s_cam_rt struct to store camera data
 * 
 * @param pov pointer to point of view coordinates
 * @param vec pointer to camera vector
 * @param fov camera field of view
 */

typedef struct s_cam_rt
{
	t_pov_rt		*pov;
	t_vec_rt		*orient_vec;
	double			fov;
	int				hsize;
	int				vsize;
	double			half_width;
	double			half_height;
	double			focal_length;
	double			pixel_width;
	double			pixel_height;
	t_vec_rt		*v_width;
	t_vec_rt		*v_height;
}				t_cam_rt;

/**
 * @brief s_light_rt struct to store light data
 * 
 * @param coord pointer to light coordinates
 * @param ratio light ratio
 * @param color pointer to light color
 */

typedef struct s_light_rt
{
	t_coord_rt		*coord;
	double			ratio;
	t_color_rt		*color;
}				t_light_rt;

// --- --- --- Geometry related structs --- --- --- //

/**
 * @brief s_sphere_rt struct to store sphere data
 * 
 * @param id sphere id
 * @param diameter sphere diameter
 * @param center pointer to sphere center coordinates
 * @param color pointer to sphere color
 * @param next pointer to next sphere
 * @param prev pointer to previous sphere
 */

typedef struct s_sphere_rt
{
	int					id;
	double				diameter;
	t_coord_rt			*center;
	t_color_rt			*color;
	struct s_sphere_rt	*next;
	struct s_sphere_rt	*prev;
}				t_sphere_rt;

/**
 * @brief s_plane_rt struct to store plane data
 * 
 * @param id plane id
 * @param coord pointer to plane coordinates
 * @param vec pointer to plane vector
 * @param color pointer to plane color
 * @param next pointer to next plane
 * @param prev pointer to previous plane
 */

typedef struct s_plane_rt
{
	int					id;
	t_coord_rt			*coord;
	t_vec_rt			*vec;
	t_color_rt			*color;
	struct s_plane_rt	*next;
	struct s_plane_rt	*prev;
}				t_plane_rt;

/**
 * 
 * @brief s_cyl_rt struct to store cylinder data
 * 
 * @param id cylinder id
 * @param diameter cylinder diameter
 * @param height cylinder height
 * @param center pointer to cylinder center coordinates
 * @param vec pointer to cylinder vector
 * @param color pointer to cylinder color
 * @param next pointer to next cylinder
 * @param prev pointer to previous cylinder
 */

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

/**
 * @struct s_main_rt t_main_rt
 * @brief s_main_rt struct to store main miniRT data
 * 
 * @param fd file descriptor
 * @param amb_counter ambient light counter
 * @param cam_counter camera counter
 * @param light_counter light counter
 * @param sphere_counter sphere counter
 * @param plane_counter plane counter
 * @param cyl_counter cylinder counter
 * @param num_windows number of windows
 * @param img pointer to mlx_image_t struct
 * @param amb pointer to ambient light
 * @param cam pointer to camera
 * @param light pointer to light
 * @param sphere pointer to sphere
 * @param plane pointer to plane
 * @param cyl pointer to cylinder
 * @param color pointer to combined color
 */

typedef struct s_main_rt
{
	int				fd;
	int				amb_counter;
	int				cam_counter;
	int				light_counter;
	int				sphere_counter;
	int				plane_counter;
	int				cyl_counter;
	int				num_windows;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_garbage		*garb_col;
	t_amb_rt		*amb;
	t_cam_rt		*cam;
	t_light_rt		*light;
	t_sphere_rt		*sphere;
	t_plane_rt		*plane;
	t_cyl_rt		*cyl;
	t_color_rt		*color;
}				t_main_rt;

/** parse_ambient:
 * @brief parses ambient light & updates main_rt struct
 * 
 * @param line The line of text containing the ambient light info
 * @param main_rt A pointer to the main_rt structure.
 * @return Returns 0 if successful, 1 if there is an error.
 */
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
// int			parser(int fd, t_main_rt *main_rt);
int			parser(t_garbage *g_c, char *f_n, t_scene_rt *s, t_main_rt * m_rt);
//parser/utils
double		ft_atod(char *str);
t_coord_rt	*parse_coord(char *str);
t_pov_rt	*parse_pov(char *str);
t_vec_rt	*parse_vec(char *str);
t_color_rt	*parse_color(char *str);
void		ft_free_all(t_main_rt *main_rt);
void		ft_free(char **str);
//mlx
mlx_t		*renderer(t_main_rt *main_rt);
void		main_rt_init(t_main_rt *main_rt);


#endif