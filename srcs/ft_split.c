/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:09:47 by daumis            #+#    #+#             */
/*   Updated: 2024/02/22 17:12:32 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

size_t	ft_len(const char *s, unsigned int start, char c)
{
	int	i;

	i = 0;
	while (s[start] != c && s[start])
	{
		start++;
		i++;
	}
	return (i);
}

int	ft_nbmots(char const *s, char c)
{
	int	i;
	int	nbmots;

	i = 0;
	nbmots = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			nbmots++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nbmots);
}

void	ft_free2(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	unsigned int	start;
	int				i;

	i = 0;
	start = 0;
	tab = malloc(sizeof(char *) * (ft_nbmots(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[start])
	{
		if (s[start] != c)
		{
			tab[i] = ft_substr(s, start, ft_len(s, start, c));
			if (!tab[i])
				return (ft_free2(tab, i), NULL);
			start += ft_len(s, start, c);
			i++;
		}
		else
			start++;
	}
	tab[i] = 0;
	return (tab);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*s1;
	size_t			slen;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	slen = ft_strlen(s);
	if (!s)
		return (NULL);
	if (len >= slen - start)
		len = slen - start;
	if (start >= slen)
		return (NULL);
	s1 = malloc((len + 1) * sizeof(char));
	if (!s1)
		return (NULL);
	while (s[start] && i++ < len)
		s1[j++] = s[start++];
	s1[j] = '\0';
	return (s1);
}
