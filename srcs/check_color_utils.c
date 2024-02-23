/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:37:33 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 17:12:32 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	signe;
	int	nb;

	i = 0;
	signe = 1;
	nb = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{	
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	nb = nb * signe;
	return (nb);
}

int	ft_isdigit(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9' && flag == 0)
			flag = 1;
		if (str[i] == ' ' && flag == 1)
			flag = 2;
		if (str[i] >= '0' && str[i] <= '9' && flag == 2)
			return (1);
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	create_rgb(int *tab, int code, t_vars *vars)
{
	int	r;
	int	g;
	int	b;

	if (!tab)
		return ;
	r = tab[0];
	g = tab[1];
	b = tab[2];
	if (code == 0)
		vars->f_color = ((r & 0xff) << 16)
			+ ((g & 0xff) << 8) + (b & 0xff);
	else
		vars->c_color = ((r & 0xff) << 16)
			+ ((g & 0xff) << 8) + (b & 0xff);
}

void	ft_free_img(t_vars *vars, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		if (vars->img[i].img)
			mlx_destroy_image(vars->mlx, vars->img[i].img);
}

int	sort_tab_utils(char **tab, int i, int k, char **tab_cpy)
{
	char	*str;

	str = ft_strtrim(tab[i], " ");
	if (!str)
		return (-1);
	if (str[0] == 'N' && k == 0)
		tab_cpy[k++] = str;
	else if (str[0] == 'S' && k == 1)
		tab_cpy[k++] = str;
	else if (str[0] == 'W' && k == 2)
		tab_cpy[k++] = str;
	else if (str[0] == 'E' && k == 3)
		tab_cpy[k++] = str;
	else if (str[0] == 'F' && k == 4)
		tab_cpy[k++] = str;
	else if (str[0] == 'C' && k == 5)
		tab_cpy[k++] = str;
	else
		free(str);
	return (k);
}
