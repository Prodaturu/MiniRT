/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 14:21:02 by sprodatu          #+#    #+#             */
/*   Updated: 2024/06/28 01:02:15 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	char	*line;
	int		fd;

	if (argc != 2)
		return (ft_putendl_fd("Error: provide .rt file", 2), 1);
	printf("%s\n", argv[1]);
	if (ft_strncmp(ft_strrchr(argv[1], '.'), ".rt", 3))
		return (ft_putendl_fd("Error: provide .rt file", 2), 1);
	printf("File is .rt\n");
	fd = open(argv[1], O_RDONLY);
	printf("File descriptor: %d\n", fd);
	line = get_next_line(fd);
	printf("%s\n", line);
	return (0);
}
/*
check argc
check argv[1] for .rt extension
parse file with gnl and split by spaces
check for elements, some cannot be missing some cannot duplicate
check syntax for each element
create a struct for each element
create a struct for each object

*/