/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:01:42 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 17:12:32 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (i);
	while (tab[i])
		i++;
	return (i);
}

int	is_environment(char c)
{
	if (c == '1' || c == '0' || c == ' ')
		return (1);
	return (0);
}

int	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	get_last(char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	i--;
	while (tab[i] == ' ' && i != 0)
		i--;
	return (i);
}

int	is_open(char **tab, int i, int j, t_check *c)
{
	if (i == 0 || i == c->size - 1 || j == c->first || j == c->last)
		return (1);
	if ((i > 0 && j > (int)ft_strlen(tab[i - 1]) - 1
			&& (tab[i][j] == '0' || tab[i][j] == ' '))
		|| (i < c->size - 1 && j > (int)ft_strlen(tab[i + 1]) - 1
		&& (tab[i][j] == '0' || tab[i][j] == ' ')))
		return (1);
	return (0);
}
