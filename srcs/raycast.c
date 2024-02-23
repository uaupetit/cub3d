/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:07:21 by psan              #+#    #+#             */
/*   Updated: 2024/02/22 16:40:34 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

//tir le rayon jus qu mur
void	raycast(t_data *data, t_vars *vars)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->sidedistx < data->sidedisty)
		{
			data->sidedistx += data->deltadistx;
			data->mapx += data->stepx;
			data->side = data->stepx < 0;
		}
		else
		{
			data->sidedisty += data->deltadisty;
			data->mapy += data->stepy;
			data->side = (data->stepy < 0) + 2;
		}
		if (vars->map[data->mapx][data->mapy] == '1')
			hit = 1;
	}
}

// position ou le mur a ete frapper, pour savoir quel pixel afficher
void	get_intersection(t_data *data, t_vars *vars)
{
	data->texwidth = vars->img[data->side].width;
	data->texheight = vars->img[data->side].height;
	if (data->side < 2)
	{
		data->perpwalldist = (data->sidedistx - data->deltadistx);
		data->wallx = data->posy + data->perpwalldist * data->raydiry;
		data->wallx -= floor(data->wallx);
		data->texx = (int)(data->wallx * (double)data->texwidth);
		if (data->raydirx > 0)
			data->texx = data->texwidth - data->texx - 1;
	}
	else
	{
		data->perpwalldist = (data->sidedisty - data->deltadisty);
		data->wallx = data->posx + data->perpwalldist * data->raydirx;
		data->wallx -= floor(data->wallx);
		data->texx = (int)(data->wallx * (double)data->texwidth);
		if (data->raydiry < 0)
			data->texx = data->texwidth - data->texx - 1;
	}
}

//hauteur mur
void	get_height(t_data *data, t_vars *vars, int x)
{
	int	line_height;

	line_height = vars->height / data->perpwalldist;
	data->drawstart = -line_height / 2 + vars->height / 2;
	data->drawend = line_height / 2 + vars->height / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	if (data->drawend >= vars->height)
		data->drawend = vars->height - 1;
	data->step = 1.0 * data->texheight / line_height;
	data->texpos = (data->drawstart - vars->height / 2 + line_height / 2)
		* data->step;
	draw_column(data, vars, x);
}

void	dda(t_data *data, t_vars *vars)
{
	int	x;

	if (!vars)
		return ;
	x = 0;
	data->posx = vars->p.x;
	data->posy = vars->p.y;
	data->dirx = vars->p.dirx;
	data->diry = vars->p.diry;
	data->planex = vars->p.plnx;
	data->planey = vars->p.plny;
	while (x < vars->width)
	{
		init_ray(data, vars, x);
		init_step(data);
		raycast(data, vars);
		get_intersection(data, vars);
		get_height(data, vars, x);
		x++;
	}
	if (vars->win)
		mlx_put_image_to_window(vars->mlx, vars->win, vars->s.img, 0, 0);
}
