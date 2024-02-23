/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:23:08 by psan              #+#    #+#             */
/*   Updated: 2024/02/22 16:40:05 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

double	deg2rad(double degree)
{
	return (degree * (M_PI / 180.0));
}

double	rotx(double dir_x, double dir_y, double radian)
{
	return (dir_x * cos(radian) - dir_y * sin(radian));
}

double	roty(double dir_x, double dir_y, double radian)
{
	return (dir_x * sin(radian) + dir_y * cos(radian));
}

double	clamp(double x, double lower, double upper)
{
	double	value;

	if (x > lower)
		value = x;
	else
		value = lower;
	if (upper < value)
		return (upper);
	return (value);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*pstr;
	size_t			i;

	pstr = (unsigned char *)s;
	i = 0;
	while (n)
	{
		pstr[i] = c;
		i++;
		n--;
	}
	return (s);
}
