#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "render_structs.h"
# include "parser.h"

# define EPSILON 1e-6

typedef struct s_main_rt
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_scene		scene;
	uint32_t	*framebuffer;
	bool		save_mode;
	char		scene_path[1024];
}	t_main_rt;

int			file_checker(int argc, char **argv, t_main_rt *rt, char *err, size_t size);
int			init_scene_struct(t_scene *scene, char *err, size_t size);
void		scene_free(t_scene *scene);
int			append_object(t_scene *scene, t_object object, char *err, size_t size);

t_vec		vec_add(t_vec a, t_vec b);
t_vec		vec_sub(t_vec a, t_vec b);
t_vec		vec_scale(t_vec v, double scale);
double		vec_dot(t_vec a, t_vec b);
t_vec		vec_cross(t_vec a, t_vec b);
double		vec_length(t_vec v);
t_vec		vec_normalize(t_vec v);

t_color		color_add(t_color a, t_color b);
t_color		color_scale(t_color color, double scale);
t_color		color_mul(t_color a, t_color b);
t_color		color_clamp(t_color color);
uint32_t	rgba_from_color(t_color color);

t_ray		make_camera_ray(const t_scene *scene, int x, int y);
void		scene_render(t_main_rt *rt);
t_color		trace_lighting(const t_scene *scene, const t_hit *hit);
t_color		trace_ray(const t_scene *scene, t_ray ray);
bool		scene_hit(const t_scene *scene, t_ray ray, double t_min, double t_max, t_hit *hit);
bool		is_in_shadow(const t_scene *scene, t_vec point, t_vec light_dir, double light_distance);
void		set_framebuffer_pixel(t_main_rt *rt, int x, int y, uint32_t color);
int			write_bmp(const t_main_rt *rt, char *err, size_t size);

int			renderer(t_main_rt *rt, char *err, size_t size);

#endif
