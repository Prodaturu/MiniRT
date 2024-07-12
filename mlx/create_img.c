/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 23:08:34 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/12 07:10:07 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

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
	return (r << 24 | g << 16 | b << 8 | a);
}

void	color_image(mlx_image_t *img, t_main_rt *main_rt)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	color = get_rgba(main_rt->amb->color->r, \
		main_rt->amb->color->g, main_rt->amb->color->b, main_rt->amb->ratio);
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

// mlx_t	*renderer(t_main_rt *main_rt)
// {
// 	mlx_t		*mlx;
// 	mlx_image_t	*img;

// 	main_rt->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
// 	mlx = main_rt->mlx;
// 	if (!mlx)
// 		return (ft_putendl_fd("Error: mlx error", 2), (void *)0);
// 	main_rt->img = mlx_new_image(mlx, WIDTH, HEIGHT);
// 	img = main_rt->img;
// 	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
// 		return (ft_putendl_fd("Error: mlx image error", 2), (void *)0);
// 	create_images(mlx, img, main_rt);
// 	mlx_key_hook(mlx, &my_keyhook, NULL);
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (mlx);
// }

int	*renderer(t_main_rt *main_rt)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		return (ft_putendl_fd("Error: mlx error", 2), (void *)0);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return (ft_putendl_fd("Error: mlx image error", 2), (void *)0);
	mlx_image_to_window(mlx, img, 0, 0);
	color_image(img, main_rt);
	mlx_key_hook(mlx, &on_keypress, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}
