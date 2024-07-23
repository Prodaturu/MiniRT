/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 23:08:34 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/23 00:43:53 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int		get_rgba(int r, int g, int b, int a);
void	my_keyhook(mlx_key_data_t keydata, void *param);

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	(void)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		exit(0);
	}
}

int	get_rgba(int r, int g, int b, int a)
{
	return ((unsigned int)r << 24 | (unsigned int)g << 16 | \
	(unsigned int)b << 8 | (unsigned int)a);
}

// void	draw_image(mlx_image_t *img, t_main_rt *main_rt)
// {
// 	int	h_index;
// 	int	w_index;

// 	h_index = 0;
// 	w_index = 0;
// 	while (h_index < main_rt->cam->height)
// 	{
// 		w_index = 0;
// 		while (w_index < main_rt->cam->width)
// 		{
// 			w_index++;
// 		}
// 		h_index++;
// 	}
// }

void	color_images(mlx_image_t *img, t_main_rt *main_rt)
{
	int			x;
	int			y;
	int			color;
	t_parser	*parser;

	x = 0;
	parser = main_rt->parser;
	color = get_rgba(parser->amb->color->r, parser->amb->color->g, \
		parser->amb->color->b, parser->amb->ratio);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			mlx_put_pixel(img, x, y, (color + x * y));
			y++;
		}
		x++;
	}
}

mlx_t	*renderer(t_main_rt *main_rt)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	main_rt->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	mlx = main_rt->mlx;
	if (!mlx)
		return (ft_putendl_fd("Error: mlx error", 2), (void *)0);
	main_rt->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img = main_rt->img;
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return (ft_putendl_fd("Error: mlx image error", 2), (void *)0);
	scene_render(main_rt);
	mlx_key_hook(mlx, &my_keyhook, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (mlx);
}
