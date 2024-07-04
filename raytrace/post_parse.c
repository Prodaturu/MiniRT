/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 22:21:20 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/04 00:34:58 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

mlx_t	init_viewport(t_main_rt *main_rt)
{
	
}

void	init_graphics(t_main_rt *main_rt)
{
	main_rt->mlx = mlx_init(WIDTH, HEIGHT, "RayTracer", true);
	if (!main_rt->mlx)
		print_msg(1, "window initialization failure");
	
}

mlx_t	*post_processing(t_main_rt *main_rt)
{
	init_viewport(main_rt);
	init_graphics(main_rt);
	// hook keypress
	// hook quit
	render(main_rt);
	mlx_loop(main_rt);
}
