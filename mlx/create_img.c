/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 23:08:34 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/01 00:30:01 by trosinsk         ###   ########.fr       */
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

void	color_image(mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (x % 2 == 0 || y % 2 == 0)
				mlx_put_pixel(img, x, y, 0x00000000);
			else
				mlx_put_pixel(img, x, y, 0xFFFFFFFF);
			y++;
		}
		x++;
	}
}

mlx_t	*create_image(t_main_rt *main_rt)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		return (ft_putendl_fd("Error: mlx error", 2), (void *)0);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return (ft_putendl_fd("Error: mlx image error", 2), (void *)0);
	main_rt->mlx = mlx;
	color_image(img);
	mlx_key_hook(mlx, &my_keyhook, NULL);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (mlx);
}
