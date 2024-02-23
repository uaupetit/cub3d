/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 11:21:17 by psan              #+#    #+#             */
/*   Updated: 2024/02/22 17:26:25 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	init_mlx(char **av, t_vars *v)
{
	v->mlx = mlx_init();
	if (!v->mlx)
		return (1);
	v->img = malloc(sizeof(t_img) * 4);
	if (!v->img)
		return (mlx_destroy_display(v->mlx), free(v->mlx), 1);
	ft_memset(v->img, 0, sizeof(t_img *));
	if (parsing(av, v, 0) == 1)
		return (free(v->img), mlx_destroy_display(v->mlx), free(v->mlx), 1);
	v->win = mlx_new_window(v->mlx, v->width, v->height, "Cub3D");
	if (!v->win)
		return (ft_free_img(v, 4), ft_free(v->map), free(v->img),
			mlx_destroy_display(v->mlx), free(v->mlx), 1);
	v->s.img = mlx_new_image(v->mlx, v->width, v->height);
	if (!v->s.img)
		return (ft_free_img(v, 4), ft_free(v->map), free(v->img),
			mlx_destroy_window(v->mlx, v->win),
			mlx_destroy_display(v->mlx), free(v->mlx), 1);
	v->s.addr = mlx_get_data_addr(v->s.img, &v->s.bpp, &v->s.ll, &v->s.endian);
	if (!v->s.addr)
		return (ft_free_img(v, 4), ft_free(v->map), free(v->img),
			mlx_destroy_image(v->mlx, v->s.img),
			mlx_destroy_window(v->mlx, v->win),
			mlx_destroy_display(v->mlx), free(v->mlx), 1);
	return (0);
}

void	init_data(t_data *data, t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map[i])
	{
		if (data->mapwidth < (int)ft_strlen(vars->map[i]))
			data->mapwidth = ft_strlen(vars->map[i]);
		i++;
	}
	data->mapheight = i;
	data->posx = vars->p.x;
	data->posy = vars->p.y;
	data->dirx = vars->p.dirx;
	data->diry = vars->p.diry;
	data->planex = vars->p.plnx;
	data->planey = vars->p.plny;
	data->minx = 64;
	data->miny = 64;
}

int	close_window(t_vars *v)
{
	int	i;

	i = 0;
	while (v->map[i])
		free(v->map[i++]);
	free(v->map);
	i = 0;
	while (i < 4)
		mlx_destroy_image(v->mlx, v->img[i++].img);
	free(v->img);
	mlx_destroy_image(v->mlx, v->s.img);
	mlx_destroy_window(v->mlx, v->win);
	v->win = NULL;
	return (0);
}

int	main_loop(t_vars *v)
{
	(void)v;
	return (0);
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac != 2)
		return (printf("Error\nNeeds a file to open\n"), 1);
	ft_memset(&vars, 0, sizeof(t_vars));
	vars.width = 640;
	vars.height = 480;
	vars.mov = 0.3;
	vars.limit = 0.6;
	vars.rot = 10;
	vars.change = 1;
	vars.scale = 8;
	if (init_mlx(av, &vars))
		return (1);
	ft_memset(&vars.data, 0, sizeof(t_data));
	init_data(&vars.data, &vars);
	dda(&vars.data, &vars);
	mlx_hook(vars.win, KeyPress, KeyPressMask, &key_pressed, &vars);
	mlx_hook(vars.win, MotionNotify, PointerMotionMask, &mouse_moved, &vars);
	mlx_hook(vars.win, ClientMessage, KeyPressMask, &close_window, &vars);
	mlx_loop_hook(vars.mlx, &main_loop, &vars);
	mlx_loop(vars.mlx);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
	return (0);
}
