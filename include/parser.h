#ifndef PARSER_H
# define PARSER_H

# include <stddef.h>
# include <stdbool.h>
# include "render_structs.h"

typedef struct s_ambient
{
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec	position;
	t_vec	direction;
	t_vec	right;
	t_vec	up;
	double	fov_degrees;
	struct s_camera	*next;
}	t_camera;

typedef struct s_light
{
	t_vec	position;
	double	ratio;
	t_color	color;
	struct s_light	*next;
}	t_light;

typedef enum e_object_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_SQUARE,
	OBJ_TRIANGLE
}	t_object_type;

typedef struct s_object
{
	t_object_type		type;
	t_vec				position;
	t_vec				direction;
	t_color				color;
	double				radius;
	double				height;
	double				size;
	t_vec				vertex_b;
	t_vec				vertex_c;
	struct s_object		*next;
}	t_object;

typedef struct s_scene
{
	bool		has_resolution;
	bool		has_ambient;
	int			width;
	int			height;
	int			window_width;
	int			window_height;
	t_ambient	ambient;
	t_camera	*cameras;
	t_camera	*active_camera;
	t_light		*lights;
	t_object	*objects;
	size_t		camera_count;
	size_t		light_count;
	size_t		object_count;
}	t_scene;

int		parse_scene_file(const char *path, t_scene *scene, char *err, size_t size);
int		parse_resolution(char **tokens, int count, t_scene *scene, char *err, size_t size);
int		parse_ambient(char **tokens, int count, t_scene *scene, char *err, size_t size);
int		parse_camera(char **tokens, int count, t_scene *scene, char *err, size_t size);
int		parse_light(char **tokens, int count, t_scene *scene, char *err, size_t size);
int		parse_sphere(char **tokens, int count, t_scene *scene, char *err, size_t size);
int		parse_plane(char **tokens, int count, t_scene *scene, char *err, size_t size);
int		parse_cylinder(char **tokens, int count, t_scene *scene, char *err, size_t size);
int		parse_square(char **tokens, int count, t_scene *scene, char *err, size_t size);
int		parse_triangle(char **tokens, int count, t_scene *scene, char *err, size_t size);
int		append_camera(t_scene *scene, t_camera camera, char *err, size_t size);
int		append_light(t_scene *scene, t_light light, char *err, size_t size);

char	**split_whitespace(const char *line, int *count);
void	free_tokens(char **tokens);
char	*trim_in_place(char *str);
bool	parse_double_strict(const char *str, double *out);
bool	parse_int_strict(const char *str, int *out);
bool	parse_vec3(const char *str, t_vec *out);
bool	parse_color_rgb(const char *str, t_color *out);
bool	parse_unit_vec(const char *str, t_vec *out);
void	set_error(char *err, size_t size, const char *fmt, ...);

#endif
