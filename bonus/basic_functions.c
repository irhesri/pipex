/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:19:24 by irhesri           #+#    #+#             */
/*   Updated: 2022/05/27 10:19:26 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//	b = 1 exit
short	error(char *str, int err, short b)
{
	if (!b)
		perror(str);
	else if (str)
	{
		my_putstr(str, 2);
		my_putstr("\n", 2);
		exit (err);
	}
	else
	{
		my_putstr(strerror(err), 2);
		my_putstr("\n", 2);
		exit(err);
	}
	return (1);
}

size_t	ft_strlen(char *str)
{
	size_t	size;

	size = 0;
	while (str && *str)
	{
		size++;
		str++;
	}
	return (size);
}

short	my_putstr(char *str, int fd)
{
	while (str && *str)
	{
		write(fd, str, 1);
		str++;
	}
	return (1);
}

short	my_strch(char *str, char c)
{
	while (str && *str && *str != c)
		str++;
	if (!str || !*str)
		return (0);
	return (1);
}

short	my_strncmp(char *str1, char *str2, int n)
{
	if (!str1 || !str2)
		return (1);
	while (n-- && *str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	return (1);
}