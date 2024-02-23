/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:20:11 by uaupetit          #+#    #+#             */
/*   Updated: 2024/02/22 17:12:32 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	check_whitespace(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (!(str[i] == ' ' || (str[i] > 8 && str[i] < 14)))
			return (1);
		i++;
	}
	return (0);
}

char	**save_map(int fd, char **tab, int i)
{
	char	*temp;
	char	**tab_cpy;

	temp = get_next_line(fd);
	while (temp != NULL)
	{
		if (check_whitespace(temp))
		{
			if (temp[ft_strlen(temp) - 1] == '\n')
				tab[i] = ft_strndup(temp, ft_strlen(temp) - 1);
			else
				tab[i] = ft_strndup(temp, ft_strlen(temp));
			if (tab[i++] == 0)
				return (free(temp), ft_free(tab), NULL);
		}
		free(temp);
		temp = get_next_line(fd);
	}
	free(temp);
	tab[i] = NULL;
	tab_cpy = sort_tab(tab, -1, 0, 0);
	if (!tab_cpy)
		return (ft_free(tab), NULL);
	return (ft_free(tab), tab_cpy);
}

int	read_map(int fd, int i, int flag)
{
	char	*temp;

	temp = get_next_line(fd);
	while (temp != NULL)
	{
		if (i <= 5 && check_whitespace(temp))
			i++;
		else if (i > 5 && check_whitespace(temp))
		{
			if (flag != 2)
				flag = 1;
			i++;
		}
		else if (i > 5 && flag)
			flag = 2;
		free(temp);
		temp = get_next_line(fd);
		last_lines(fd, &flag, &temp);
	}
	if (flag == 3)
		return (printf("Error\ninvalid map\n"), free(temp), -1);
	return (free(temp), i);
}

int	check_extension(char **av)
{
	int	i;

	i = ft_strlen(av[1]);
	if (i > 4)
	{
		if ((av[1][i -1] != 'b') || (av[1][i - 2] != 'u')
		|| (av[1][i - 3] != 'c') || (av[1][i - 4] != '.'))
			return (1);
	}
	return (0);
}

int	parsing(char **av, t_vars *vars, int i)
{
	char	**tab;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1 || check_extension(av) > 0)
		return (printf("Error\nWrong file\n"), 1);
	tab = NULL;
	i = read_map(fd, 0, i);
	if (close(fd) == -1 || i == -1)
		return (1);
	tab = malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (printf("Error\nmalloc problem\n"), 1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_free(tab), 1);
	tab = save_map(fd, tab, 0);
	if (!tab)
		return (1);
	if (close(fd) == -1)
		return (ft_free(tab), 1);
	if (check_file_content(tab, vars))
		return (ft_free(tab),
			printf("Error\nwrong file content or invalid map\n"), 1);
	return (ft_free(tab), 0);
}
