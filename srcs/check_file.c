/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:58:08 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 17:12:32 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	check_map(char **tab, t_vars *vars, int i, int j)
{
	init_var(&vars->c, 0, tab);
	while (tab[++i])
	{
		init_var(&vars->c, 1, tab);
		j = 0;
		while (tab[i][j])
		{
			if (is_environment(tab[i][j]) || is_player(tab[i][j]))
			{
				if (process_cell(tab, vars, i, j))
					return (1);
				j++;
			}
			else
				return (1);
		}
	}
	if (vars->c.flag == 0 || copy_map(tab, vars) == 1)
		return (1);
	return (0);
}

int	check_color(char *str, t_vars *vars, int code, int i)
{
	char	**color_split;
	int		tab[3];

	if (!str)
		return (1);
	color_split = ft_split(str, ',');
	if (!color_split)
		return (1);
	while (color_split[i] && color_split[i][0] != '\n')
		i++;
	if (i != 3)
		return (ft_free(color_split), 1);
	i = -1;
	while (color_split[++i] && color_split[i][0] != '\n')
	{
		if (ft_isdigit(color_split[i]))
			return (ft_free(color_split), 1);
		tab[i] = ft_atoi(color_split[i]);
		if (tab[i] < 0 || tab[i] > 255)
			return (ft_free(color_split), 1);
	}
	i = 0;
	while (color_split[i])
		free(color_split[i++]);
	return (free(color_split), create_rgb(tab, code, vars), 0);
}

int	check_texture(char *str, t_vars *vars, int code)
{
	t_img	img;

	ft_memset(&vars->img[code], 0, sizeof(t_img));
	vars->img[code].img = NULL;
	if (!str)
		return (1);
	img.img = mlx_xpm_file_to_image(vars->mlx, str, &img.width, &img.height);
	if (!img.img)
		return (1);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.ll, &img.endian);
	if (!img.addr)
	{
		mlx_destroy_image(vars->mlx, img.img);
		return (1);
	}
	vars->img[code] = img;
	return (0);
}

int	check_file_content(char **tab, t_vars *vars)
{
	int	error;

	if (!tab || !tab[0])
		return (1);
	if (tab[0][0] == 'N' && tab[0][1] == 'O')
	{
		error = check_no(tab, vars);
		if (error)
			return (error);
	}
	else
		return (1);
	if (check_map(tab + 6, vars, -1, 0) == 1)
		return (ft_free_img(vars, 4), 1);
	return (0);
}

char	**sort_tab(char **tab, int i, int flag, int k)
{
	char	**tab_cpy;

	tab_cpy = malloc(sizeof(char *) * (tab_size(tab) + 1));
	if (!tab_cpy)
		return (NULL);
	*tab_cpy = NULL;
	while (tab[++i])
	{
		k = sort_tab_utils(tab, i, k, tab_cpy);
		if (k == 6)
			break ;
		if (k == -1)
			return (ft_free(tab_cpy), NULL);
		if (k != flag)
		{
			flag = k;
			i = -1;
		}
	}
	i = 5;
	if (tab[i] && tab[i + 1])
		while (tab[++i])
			tab_cpy[k++] = ft_strndup(tab[i], ft_strlen(tab[i]));
	tab_cpy[k] = NULL;
	return (tab_cpy);
}
