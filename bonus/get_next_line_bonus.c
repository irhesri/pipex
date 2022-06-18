/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 08:11:49 by irhesri           #+#    #+#             */
/*   Updated: 2021/12/18 08:12:30 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

static	int	ft_strcopy(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (s2[i] && (s2[i] != c))
	{
		s1[i] = s2[i];
		i++;
	}
	if (c == '\n' && (s2[i] == '\n'))
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (i);
}

char	*ft_endlsplit(char *s1, char *s2, int *size)
{
	int		size1;
	int		i;
	char	*str;

	size1 = (*size) + BUFFER_SIZE + 1;
	i = 0;
	str = (char *) malloc(sizeof(char) * size1);
	if (!str)
		return (NULL);
	if (s1 && *s1)
		i = ft_strcopy(str, s1, '\0');
	(*size) = i;
	i = ft_strcopy(&str[i], s2, '\n');
	(*size) += i;
	ft_strcopy(s2, &s2[i], '\0');
	free (s1);
	return (str);
}

char	*read_next_line(char *str, int fd)
{
	char	*s;
	ssize_t	len;
	int		size;

	size = 0;
	s = NULL;
	s = ft_endlsplit(s, str, &size);
	if (size > 0 && s[size - 1] == '\n')
		return (s);
	len = 1;
	while (len > 0)
	{
		len = read(fd, str, BUFFER_SIZE);
		if (len > 0)
		{
			str[len] = '\0';
			s = ft_endlsplit(s, str, &size);
			if (size > 0 && s[size - 1] == '\n')
				return (s);
		}
	}
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*s;

	if (fd < 0 || (BUFFER_SIZE <= 0) || fd > FOPEN_MAX)
		return (NULL);
	if (!str)
	{
		str = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	s = read_next_line(str, fd);
	if (*s == '\0')
	{
		free (str);
		free (s);
		str = NULL;
		return (NULL);
	}
	return (s);
}
