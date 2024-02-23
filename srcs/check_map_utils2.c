/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:47:17 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 17:12:32 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	is_whitespace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

void	fill_player(t_vars *vars, char c)
{
	int		dx;
	int		dy;
	int		p;

	dx = 1;
	dy = 1;
	p = 1;
	if (c == 'N' || c == 'S')
	{
		if (c == 'N')
			dx = -1;
		dy = 0;
		p = -1;
	}
	else if (c == 'W' || c == 'E')
	{
		if (c == 'W')
			dy = -1;
		dx = 0;
	}
	vars->p.dirx = dx;
	vars->p.diry = dy;
	vars->p.plnx = p * vars->p.diry;
	vars->p.plny = p * vars->p.dirx;
}

int	copy_map(char **tab, t_vars *vars)
{
	int	i;
	int	size;

	i = 0;
	size = tab_size(tab);
	vars->map = malloc(sizeof(char *) * (size + 1));
	if (!vars->map)
		return (1);
	while (tab[i])
	{
		vars->map[i] = ft_replace_space(tab[i], ft_strlen(tab[i]));
		if (!vars->map[i])
			return (1);
		i++;
	}
	vars->map[i] = NULL;
	return (0);
}

char	*ft_replace_space(const char *s, int len)
{
	char	*dest;
	int		i;

	dest = malloc((len + 1) * sizeof(const char));
	if (!dest)
		return (0);
	i = 0;
	while (i < len)
	{
		if (s[i] == ' ')
			dest[i] = '0';
		else
			dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
