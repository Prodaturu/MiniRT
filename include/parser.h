/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:30:34 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/27 07:33:31 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define VALID_SET "ACLsplcy +-.0123456789,\n"

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	AMBIENT,
	CAMERA,
	LIGHT,
	UNKNOWN
}	t_object_type;

typedef struct s_object
{
	t_object_type		type;
	double				position[3];
	double				orientation[3];
	double				diameter;
	double				height;
	double				intensity;
	double				color[3];
	double				fov;
	struct s_object		*next;
}						t_object;

// @param type object type
// @param id object id
// @param next pointer to next object
typedef struct s_object
{
	t_object_type	type;
	int				id;
	struct s_object	*next;
}	t_object;

#endif

// // typedef struct s_scene_rt
// // {
// // 	int					sphere_count;
// // 	int					plane_count;
// // 	int					cylinder_count;
// // }			t_scene_rt;
// /**
//  * @brief s_vec_rt struct to store object vectors
//  * 
//  * @param vc_x vector component in x direction
//  * @param vc_y vector component in y direction
//  * @param vc_z vector component in z direction
//  */

// typedef struct s_vec_rt
// {
// 	double			vc_x;
// 	double			vc_y;
// 	double			vc_z;
// }				t_vec_rt;

// /**
//  * @brief s_pov_rt struct to store point of view coordinates
//  * 
//  * @param x point of view x coordinate
//  * @param y point of view y coordinate
//  * @param z point of view z coordinate
//  */

// typedef struct s_coord_rt
// {
// 	double			co_x;
// 	double			co_y;
// 	double			co_z;
// }				t_coord_rt;

// /**
//  * @brief color struct to store color data
//  * @param r red color value
//  * @param g green color value
//  * @param b blue color value
 
//  */

// typedef struct s_color_rt
// {
// 	int				r;
// 	int				g;
// 	int				b;
// }				t_color_rt;

// /**
//  * @brief s_amb_rt struct to store ambient light data
//  * 
//  * @param ratio ambient light ratio
//  * @param color pointer to ambient light color
//  */

// typedef struct s_amb_rt
// {
// 	double			ratio;
// 	t_color_rt		*color;
// }				t_amb_rt;

// /**
//  * @brief s_pov_rt struct to store object coordinates
//  * 
//  * @param pv_x x coordinate
//  * @param pv_y y coordinate
//  * @param pv_z z coordinate
//  */
// typedef struct s_pov_rt
// {
// 	double			pv_x;
// 	double			pv_y;
// 	double			pv_z;
// }				t_pov_rt;

// /**
//  * @brief s_light_rt struct to store light data
//  * 
//  * @param coord pointer to light coordinates
//  * @param ratio light ratio
//  * @param color pointer to light color
//  */

// typedef struct s_light_rt
// {
// 	t_coord_rt		*coord;
// 	double			ratio;
// 	t_color_rt		*color;
// }				t_light_rt;

// /**
//  * @brief s_cam_rt struct to store camera data
//  * 
//  * @param orient_vec pointer to camera orientation vector
//  * @param start_pixel pointer to start pixel coordinates
//  * @param v_cam_canvas pointer to camera canvas vector
//  * @param v_width pointer to width vector
//  * @param v_height pointer to height vector
//  * @param pov pointer to point of view coordinates
//  * @param half_width half width of the camera
//  * @param half_height half height of the camera
//  * @param focal_length camera focal length
//  * @param pixel_width pixel width
//  * @param pixel_height pixel height
//  * @param fov camera field of view
//  * @param hsize horizontal size
//  * @param vsize vertical size
//  */

// typedef struct s_cam_rt
// {
// 	t_pov_rt		*pov;
// 	t_vec_rt		*orient_vec;
// 	double			fov;
// 	int				hsize;
// 	int				vsize;
// }				t_cam_rt;

// // --- --- --- Geometry related structs --- --- --- //

// /**
//  * @brief s_sphere_rt struct to store sphere data
//  * 
//  * @param id sphere id
//  * @param diameter sphere diameter
//  * @param center pointer to sphere center coordinates
//  * @param color pointer to sphere color
//  * @param next pointer to next sphere
//  * @param prev pointer to previous sphere
//  */

// typedef struct s_sphere_rt
// {
// 	int					id;
// 	double				diameter;
// 	t_coord_rt			*center;
// 	t_color_rt			*color;
// 	struct s_sphere_rt	*next;
// 	struct s_sphere_rt	*prev;
// }				t_sphere_rt;

// /**
//  * @brief s_plane_rt struct to store plane data
//  * 
//  * @param id plane id
//  * @param coord pointer to plane coordinates
//  * @param vec pointer to plane vector
//  * @param color pointer to plane color
//  * @param next pointer to next plane
//  * @param prev pointer to previous plane
//  */

// typedef struct s_plane_rt
// {
// 	int					id;
// 	t_coord_rt			*coord;
// 	t_vec_rt			*vec;
// 	t_color_rt			*color;
// 	struct s_plane_rt	*next;
// 	struct s_plane_rt	*prev;
// }				t_plane_rt;

// /**
//  * 
//  * @brief s_cyl_rt struct to store cylinder data
//  * 
//  * @param id cylinder id
//  * @param diameter cylinder diameter
//  * @param height cylinder height
//  * @param center pointer to cylinder center coordinates
//  * @param vec pointer to cylinder vector
//  * @param color pointer to cylinder color
//  * @param next pointer to next cylinder
//  * @param prev pointer to previous cylinder
//  */

// typedef struct s_cyl_rt
// {
// 	int				id;
// 	double			diameter;
// 	double			height;
// 	t_coord_rt		*center;
// 	t_vec_rt		*vec;
// 	t_color_rt		*color;
// 	struct s_cyl_rt	*next;
// 	struct s_cyl_rt	*prev;
// }				t_cyl_rt;

// /**
//  * @struct parser struct to store the parsed data
//  * @brief struct to store the parsed data
//  * 
//  * @param fd file descriptor
//  * @param amb_counter ambient light counter
//  * @param cam_counter camera counter
//  * @param light_counter light counter
//  * @param sphere_counter sphere counter
//  * @param plane_counter plane counter
//  * @param cyl_counter cylinder counter
//  * @param num_windows number of windows
//  * @param img pointer to mlx_image_t struct
//  * @param amb pointer to ambient light
//  * @param cam pointer to camera
//  * @param light pointer to light
//  * @param sphere pointer to sphere
//  * @param plane pointer to plane
//  * @param cyl pointer to cylinder
//  * @param color pointer to combined color
//  */

// typedef enum s_object_type
// {
// 	SPHERE,
// 	CYLINDER,
// 	PLANE
// }			t_object_type;

// typedef struct s_object
// {
// 	t_object_type	type;
// 	int				counter;
// 	int				id;
// 	t_sphere_rt		*sphere;
// 	t_plane_rt		*plane;
// 	t_cyl_rt		*cylinder;
// 	t_color_rt		*color;
// 	struct s_object	*next;
// }	t_object;

// typedef struct s_objects {
// 	t_object	*object;
// 	int			count;
// }				t_objects;

// typedef struct s_parser
// {
// 	int			fd;
// 	int			amb_counter;
// 	int			cam_counter;
// 	int			light_counter;
// 	int			sphere_counter;
// 	int			plane_counter;
// 	int			cyl_counter;
// 	void		*garbage_head;
// 	t_objects	*objects;
// 	t_amb_rt	*amb;
// 	t_cam_rt	*cam;
// 	t_light_rt	*light;
// 	t_sphere_rt	*sphere;
// 	t_plane_rt	*plane;
// 	t_cyl_rt	*cyl;
// 	t_color_rt	*color;
// }			t_parser;

// // --- --- --- parser.c --- --- --- //

// /**
//  * @brief function to parse the objects in the scene
//  * 
//  * @param file_name name of the file to parse
//  * @param scene pointer to the scene struct
//  * 
//  * @details This function will parse the objects
//  * in the scene and update the scene struct
//  */
// // int	parser(t_garbage *g_c, char *file_n, t_scene *scene, t_parser *m);
// int			parse_line(char *line, t_parser *parser);

// /** parse_ambient:
//  * @brief parses ambient light & updates parser struct
//  * 
//  * @param line The line of text containing the ambient light info
//  * @param parser A pointer to the parser structure.
//  * @return Returns 0 if successful, 1 if there is an error.
//  */
// int			parse_ambient(char *line, t_parser *parser);
// //camera
// int			parse_camera(char *line, t_parser *parser);
// //light
// int			parse_light(char *line, t_parser *parser);
// //sphere
// int			parse_sphere(char *line, t_parser *parser);
// //plane
// int			parse_plane(char *line, t_parser *parser);
// //cylinder
// int			parse_cylinder(char *line, t_parser *parser);
// //parser
// int			parse_line(char *line, t_parser *parser);
// // int			parser(int fd, t_parser *parser);
// //parser/utils
// double		ft_atod(char *str);
// t_coord_rt	*parse_coord(char *str, t_parser *parser);
// t_pov_rt	*parse_pov(char *str, t_parser *parser);
// t_vec_rt	*parse_vec(char *st, t_parser *parser);
// t_color_rt	*parse_color(char *str, t_parser *parser);
// void		ft_free(char **str);
// int			err_msg(t_garbage *garb_col, int ex_flag, char *msg, int ret);