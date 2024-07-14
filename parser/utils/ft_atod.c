/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 16:39:44 by trosinsk          #+#    #+#             */
/*   Updated: 2024/07/15 01:07:59 by trosinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

bool	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

bool	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

float	fract_part(char *str)
{
	int		i;
	double	result;
	int		power;

	i = 0;
	result = 0;
	power = 1;
	while (is_num(str[i]))
	{
		result = result * 10 + str[i] - '0';
		power *= 10;
		i++;
	}
	return (result / power);
}

double	ft_atod(char *str)
{
	int		sign;
	double	result;

	result = 0.0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (*str == '-')
	{
		str++;
		sign = -1;
	}
	if (*str == '+')
		str++;
	while (*str != '.' && is_num(*str))
	{
		result = result * 10.0 + *str - '0';
		str++;
	}
	if (*str == '.')
	{
		str++;
		result += fract_part(&*str);
	}
	return (result * sign);
}
