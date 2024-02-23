/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:07:37 by psan              #+#    #+#             */
/*   Updated: 2024/02/22 16:40:11 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->ll + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	img_pixel_get(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->ll + x * (img->bpp / 8));
	return (*(int *)pixel);
}

void	draw_pixel(t_data *data, t_vars *vars, int x, int y)
{
	int	x_scale;
	int	y_scale;

	y_scale = clamp(data->posx + (y - 0.5 - data->miny / 2) / vars->scale,
			0, data->mapheight - 1);
	x_scale = clamp(data->posy + (x - 0.5 - data->minx / 2) / vars->scale,
			0, ft_strlen(vars->map[y_scale]) - 1);
	if (y_scale == (int)vars->p.x && x_scale == (int)vars->p.y)
		img_pixel_put(&vars->s, x, y, 0xff0000);
	else if (vars->map[y_scale][x_scale] == '0'
		|| is_player(vars->map[y_scale][x_scale]))
		img_pixel_put(&vars->s, x, y, 0x222222);
	else
		img_pixel_put(&vars->s, x, y, 0xdddddd);
}

void	draw_minimap(t_data *data, t_vars *vars, int x, int *y)
{
	while (*y < data->miny)
	{
		if (*y >= data->drawstart)
		{
			data->texy = (int)data->texpos & (data->texheight - 1);
			data->texpos += data->step;
		}
		draw_pixel(data, vars, x, *y);
		*y += 1;
	}
}

void	draw_column(t_data *data, t_vars *vars, int x)
{
	int		y;
	t_img	img;

	y = 0;
	img = vars->img[data->side];
	vars->color = vars->c_color;
	if (x < data->minx)
		draw_minimap(data, vars, x, &y);
	while (y < data->drawstart)
		img_pixel_put(&vars->s, x, y++, vars->color);
	while (y <= data->drawend)
	{
		data->texy = (int)data->texpos & (data->texheight - 1);
		data->texpos += data->step;
		vars->color = img_pixel_get(&img, data->texx, data->texy);
		img_pixel_put(&vars->s, x, y++, vars->color);
	}
	vars->color = vars->f_color;
	while (y < vars->height)
		img_pixel_put(&vars->s, x, y++, vars->color);
}
