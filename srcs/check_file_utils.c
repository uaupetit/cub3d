/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:05:42 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 17:12:32 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	process_cell(char **tab, t_vars *vars, int i, int j)
{
	if (vars->c.first < 0)
	{
		vars->c.first = 0;
		vars->c.last = ft_strlen(tab[i]) - 1;
	}
	if (tab[i][j] == '0' && is_open(tab, i, j, &vars->c))
		return (1);
	if (tab[i][j] == ' ' && is_open(tab, i, j, &vars->c))
		return (1);
	if (is_player(tab[i][j]))
	{
		vars->p.x = i + 0.5;
		vars->p.y = j + 0.5;
		fill_player(vars, tab[i][j]);
		vars->c.flag += 1;
		if (vars->c.flag > 1 || is_open(tab, i, j, &vars->c))
			return (1);
	}
	return (0);
}

void	init_var(t_check *c, int flag, char **tab)
{
	if (flag == 0)
	{
		c->size = tab_size(tab);
		c->flag = 0;
	}
	else if (flag == 1)
	{
		c->first = -1;
		c->last = -1;
	}
}

int	fs(char *s)
{
	int	i;

	i = 2;
	while (s[i] && s[i] == ' ')
		i++;
	return (i);
}

int	check_f(char **tab, t_vars *vars)
{
	int	error;

	error = 0;
	if (ft_strlen(tab[0]) <= 1 || check_color(tab[0] + 1, vars, 0, 0))
		return (ft_free_img(vars, 0), 1);
	else if (ft_strlen(tab[1]) <= 1 || (tab[1][0] != 'C'
		|| check_color(tab[1] + 1, vars, 1, 0)))
		return (ft_free_img(vars, 0), 1);
	else if (ft_strlen(tab[2]) <= 2 || (tab[2][0] != 'N' || tab[2][1] != 'O'
		|| check_texture(tab[2] + fs(tab[0]), vars, 0)))
		return (ft_free_img(vars, 0), 1);
	else if (ft_strlen(tab[3]) <= 2 || (tab[3][0] != 'S' || tab[3][1] != 'O'
		|| check_texture(tab[3] + fs(tab[1]), vars, 1)))
		return (ft_free_img(vars, 1), 1);
	else if (ft_strlen(tab[4]) <= 2 || (tab[4][0] != 'W' || tab[4][1] != 'E'
		|| check_texture(tab[4] + fs(tab[2]), vars, 2)))
		return (ft_free_img(vars, 2), 1);
	else if (ft_strlen(tab[5]) <= 2 || (tab[5][0] != 'E' || tab[5][1] != 'A'
		|| check_texture(tab[5] + fs(tab[3]), vars, 3)))
		return (ft_free_img(vars, 3), 1);
	return (error);
}

int	check_no(char **tab, t_vars *vars)
{
	if (ft_strlen(tab[0]) <= 2 || check_texture(tab[0] + fs(tab[0]), vars, 0))
		return (ft_free_img(vars, 0), 1);
	else if (ft_strlen(tab[1]) <= 2 || tab[1][0] != 'S' || tab[1][1] != 'O'
		|| check_texture(tab[1] + fs(tab[1]), vars, 1))
		return (ft_free_img(vars, 1), 1);
	else if (ft_strlen(tab[2]) <= 2 || tab[2][0] != 'W' || tab[2][1] != 'E'
		|| check_texture(tab[2] + fs(tab[2]), vars, 2))
		return (ft_free_img(vars, 2), 1);
	else if (ft_strlen(tab[3]) <= 2 || tab[3][0] != 'E' || tab[3][1] != 'A'
		|| check_texture(tab[3] + fs(tab[3]), vars, 3))
		return (ft_free_img(vars, 3), 1);
	else if (ft_strlen(tab[4]) <= 1 || tab[4][0] != 'F'
		|| check_color(tab[4] + 1, vars, 0, 0)
		|| ft_strlen(tab[5]) <= 1 || tab[5][0] != 'C'
		|| check_color(tab[5] + 1, vars, 1, 0))
		return (ft_free_img(vars, 4), 1);
	return (0);
}
