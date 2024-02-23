/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:27:13 by psan              #+#    #+#             */
/*   Updated: 2024/02/22 17:23:35 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_index(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		if (*s == '\n')
			return (i);
		i++;
		s++;
	}
	return (-1);
}

char	*ft_strndup(const char *s, int len)
{
	char	*dest;
	int		i;

	dest = malloc((len + 1) * sizeof(const char));
	if (!dest)
		return (0);
	i = 0;
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		s1_len;
	int		s2_len;
	int		k;
	char	*ptr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *) malloc(s1_len + s2_len + 1);
	if (!ptr)
		return (0);
	k = 0;
	while (k < (s1_len + s2_len))
	{
		if (s1_len && k < s1_len)
			ptr[k] = s1[k];
		else
			ptr[k] = s2[k - s1_len];
		k++;
	}
	ptr[k] = '\0';
	free(s1);
	return (ptr);
}

char	*ft_realloc(char *buffer, int len, int start)
{
	int		i;
	char	*swap;

	i = 0;
	if (!len)
	{
		free(buffer);
		return (0);
	}
	swap = malloc(len * sizeof(char));
	if (!swap)
		return (0);
	while (len > 0)
	{
		swap[i] = buffer[start + 1 + i];
		i++;
		len--;
	}
	free(buffer);
	buffer = swap;
	return (buffer);
}
