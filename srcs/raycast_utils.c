/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:22:59 by psan              #+#    #+#             */
/*   Updated: 2024/02/22 16:40:18 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

//calcul distance entre joueur et mur et entre mur et mur d apres
void	init_ray(t_data *data, t_vars *vars, int x)
{
	data->camerax = 2 * x / (double)(vars->width) - 1;
	data->raydirx = data->dirx + data->planex * data->camerax;
	data->raydiry = data->diry + data->planey * data->camerax;
	data->mapx = data->posx;
	data->mapy = data->posy;
	if (data->raydirx == 0)
		data->deltadistx = 1e30;
	else
		data->deltadistx = fabs(1 / data->raydirx);
	if (data->raydiry == 0)
		data->deltadisty = 1e30;
	else
		data->deltadisty = fabs(1 / data->raydiry);
}

//donne la direction du tir de rayon
void	init_step(t_data *data)
{
	if (data->raydirx < 0)
	{
		data->stepx = -1;
		data->sidedistx = (data->posx - data->mapx) * data->deltadistx;
	}
	else
	{
		data->stepx = 1;
		data->sidedistx = (data->mapx + 1.0 - data->posx) * data->deltadistx;
	}
	if (data->raydiry < 0)
	{
		data->stepy = -1;
		data->sidedisty = (data->posy - data->mapy) * data->deltadisty;
	}
	else
	{
		data->stepy = 1;
		data->sidedisty = (data->mapy + 1.0 - data->posy) * data->deltadisty;
	}
}
