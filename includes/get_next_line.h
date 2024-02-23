/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:47:30 by psan              #+#    #+#             */
/*   Updated: 2022/11/23 11:04:47 by psan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(const char *str);
int		ft_index(char *s);
char	*ft_realloc(char *buffer, int len, int start);
char	*ft_strndup(const char *s, int len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_return_line(char **s);
char	*get_next_line(int fd);

#endif
