/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:38:49 by psan              #+#    #+#             */
/*   Updated: 2024/02/22 17:23:30 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_return_line(char **s)
{
	char	*to_return;

	if (!*s)
	{
		free(*s);
		return (0);
	}
	if (ft_index(*s) >= 0)
	{
		to_return = ft_strndup(*s, ft_index(*s) + 1);
		*s = ft_realloc(*s, ft_strlen(*s) - ft_index(*s), ft_index(*s));
	}
	else
	{
		to_return = ft_strndup(*s, ft_strlen(*s));
		if (ft_strlen(to_return))
			*s = ft_realloc(*s, 0, 0);
		else
		{
			free(to_return);
			*s = ft_realloc(*s, 0, 0);
			return (0);
		}
	}
	return (to_return);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*s_tmp;
	int			read_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	read_size = 1;
	while (read_size && ft_index(s_tmp) == -1)
	{
		buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size < 0)
		{
			free(buf);
			return (0);
		}
		if (read_size)
		{
			buf[read_size] = '\0';
			s_tmp = ft_strjoin(s_tmp, buf);
		}
		free(buf);
	}
	return (ft_return_line(&s_tmp));
}
