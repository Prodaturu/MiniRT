/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sprodatu <sprodatu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 23:15:00 by sprodatu          #+#    #+#             */
/*   Updated: 2024/07/24 00:56:10 by sprodatu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include <fcntl.h>
#include <unistd.h>

static void	write_u16(unsigned char *dst, uint16_t value)
{
	dst[0] = (unsigned char)(value & 0xFF);
	dst[1] = (unsigned char)((value >> 8) & 0xFF);
}

static void	write_u32(unsigned char *dst, uint32_t value)
{
	dst[0] = (unsigned char)(value & 0xFF);
	dst[1] = (unsigned char)((value >> 8) & 0xFF);
	dst[2] = (unsigned char)((value >> 16) & 0xFF);
	dst[3] = (unsigned char)((value >> 24) & 0xFF);
}

static int	build_bmp_path(const t_main_rt *rt, char *out, size_t size)
{
	const char	*ext;
	size_t		base_len;

	ext = strrchr(rt->scene_path, '.');
	base_len = strlen(rt->scene_path);
	if (ext != NULL && strcmp(ext, ".rt") == 0)
		base_len = (size_t)(ext - rt->scene_path);
	if (base_len + 5 >= size)
		return (0);
	memcpy(out, rt->scene_path, base_len);
	memcpy(out + base_len, ".bmp", 5);
	return (1);
}

int	write_bmp(const t_main_rt *rt, char *err, size_t size)
{
	unsigned char	header[54];
	char			path[1024];
	int				fd;
	int				row;
	int				col;
	int				padding;
	int				row_size;
	uint32_t		color;
	unsigned char	pad[3];

	if (rt->framebuffer == NULL)
		return (set_error(err, size, "framebuffer is empty"), 0);
	if (!build_bmp_path(rt, path, sizeof(path)))
		return (set_error(err, size, "failed to derive bmp output path"), 0);
	memset(header, 0, sizeof(header));
	padding = (4 - ((rt->scene.width * 3) % 4)) % 4;
	row_size = rt->scene.width * 3 + padding;
	header[0] = 'B';
	header[1] = 'M';
	write_u32(header + 2, (uint32_t)(54 + row_size * rt->scene.height));
	write_u32(header + 10, 54);
	write_u32(header + 14, 40);
	write_u32(header + 18, (uint32_t)rt->scene.width);
	write_u32(header + 22, (uint32_t)rt->scene.height);
	write_u16(header + 26, 1);
	write_u16(header + 28, 24);
	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0 || write(fd, header, 54) != 54)
		return (set_error(err, size, "failed to write bmp header"), fd >= 0 ? close(fd) : 0, 0);
	memset(pad, 0, sizeof(pad));
	row = rt->scene.height - 1;
	while (row >= 0)
	{
		col = 0;
		while (col < rt->scene.width)
		{
			color = rt->framebuffer[(size_t)row * (size_t)rt->scene.width + (size_t)col];
			header[0] = (unsigned char)((color >> 8) & 0xFF);
			header[1] = (unsigned char)((color >> 16) & 0xFF);
			header[2] = (unsigned char)((color >> 24) & 0xFF);
			if (write(fd, header, 3) != 3)
				return (close(fd), set_error(err, size, "failed to write bmp pixel data"), 0);
			col++;
		}
		if (padding > 0 && write(fd, pad, padding) != padding)
			return (close(fd), set_error(err, size, "failed to write bmp padding"), 0);
		row--;
	}
	close(fd);
	return (1);
}
