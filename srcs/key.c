/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:18:36 by psan              #+#    #+#             */
/*   Updated: 2024/02/22 16:40:13 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	key_move_ns(int keycode, t_vars *v)
{
	double	newx;
	double	newy;
	int		dir;

	if (keycode != XK_w && keycode != XK_s)
		return (1);
	dir = 1;
	if (keycode == XK_s)
		dir = -1;
	newx = v->p.x + dir * v->p.dirx * v->limit;
	newy = v->p.y + dir * v->p.diry * v->limit;
	if (v->map[(int)v->p.x][(int)newy] == '1'
		|| v->map[(int)newx][(int)v->p.y] == '1'
		|| v->map[(int)newx][(int)newy] == '1')
		return (1);
	v->p.x = v->p.x + dir * v->p.dirx * v->mov;
	v->p.y = v->p.y + dir * v->p.diry * v->mov;
	return (0);
}

int	key_move_we(int keycode, t_vars *v)
{
	double	newx;
	double	newy;
	int		dir;

	if (keycode != XK_a && keycode != XK_d)
		return (1);
	dir = 1;
	if (keycode == XK_d)
		dir = -1;
	newx = v->p.x + rotx(v->p.dirx, v->p.diry, deg2rad(dir * 90)) * v->limit;
	newy = v->p.y + roty(v->p.dirx, v->p.diry, deg2rad(dir * 90)) * v->limit;
	if (v->map[(int)v->p.x][(int)newy] == '1'
		|| v->map[(int)newx][(int)v->p.y] == '1'
		|| v->map[(int)newx][(int)newy] == '1')
		return (1);
	v->p.x = newx;
	v->p.y = newy;
	return (0);
}

int	key_rotation(int keycode, t_vars *v)
{
	double	old_dir_x;
	double	old_pln_x;
	int		dir;

	if (keycode != XK_Left && keycode != XK_Right)
		return (1);
	dir = 1;
	if (keycode == XK_Right)
		dir = -1;
	old_dir_x = v->p.dirx;
	v->p.dirx = rotx(v->p.dirx, v->p.diry, dir * deg2rad(v->rot));
	v->p.diry = roty(old_dir_x, v->p.diry, dir * deg2rad(v->rot));
	old_pln_x = v->p.plnx;
	v->p.plnx = rotx(v->p.plnx, v->p.plny, dir * deg2rad(v->rot));
	v->p.plny = roty(old_pln_x, v->p.plny, dir * deg2rad(v->rot));
	return (0);
}

int	key_pressed(int keycode, t_vars *v)
{
	if (!v)
		return (1);
	if (keycode == XK_Escape)
		close_window(v);
	if (key_move_ns(keycode, v) == 0
		|| key_move_we(keycode, v) == 0
		|| key_rotation(keycode, v) == 0)
	{
		if (!v->win)
			return (1);
		mlx_clear_window(v->mlx, v->win);
		dda(&v->data, v);
	}
	return (0);
}

int	mouse_moved(int x, int y, t_vars *v)
{
	double	old_dir_x;
	double	old_pln_x;
	int		dir;

	(void)y;
	if (!v)
		return (1);
	dir = 1;
	if (x >= v->width / 2)
		dir = -1;
	old_dir_x = v->p.dirx;
	v->p.dirx = rotx(v->p.dirx, v->p.diry, dir * deg2rad(v->rot));
	v->p.diry = roty(old_dir_x, v->p.diry, dir * deg2rad(v->rot));
	old_pln_x = v->p.plnx;
	v->p.plnx = rotx(v->p.plnx, v->p.plny, dir * deg2rad(v->rot));
	v->p.plny = roty(old_pln_x, v->p.plny, dir * deg2rad(v->rot));
	if (!v->win)
		return (1);
	mlx_clear_window(v->mlx, v->win);
	dda(&v->data, v);
	return (0);
}
