/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 09:46:21 by irhesri           #+#    #+#             */
/*   Updated: 2022/05/20 09:46:23 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

typedef struct s_struct
{
	int				data;
	struct s_struct	*next;
}	t_struct;

static short	my_error(char **str, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free (str[i++]);
	free (str);
	write(1, "allocation error\n", 17);
	exit (1);
}

static void	add_back(t_struct **lst, int n)
{
	static t_struct	*last;
	t_struct		*new;

	new = (t_struct *) malloc(sizeof(t_struct));
	new->data = n;
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		last = new;
		return ;
	}
	last->next = new;
	last = new;
}

static t_struct	*get_size(char *str, char c, short b)
{
	t_struct	*size;
	int			i;

	size = NULL;
	add_back(&size, 0);
	while (*str)
	{
		i = 0;
		while (*str && *str != c)
		{
			str++;
			i++;
		}
		if (b || i)
		{
			add_back(&size, i);
			size->data++;
		}
		if (*str)
			str++;
	}
	return (size);
}

static	char	**fill(t_struct *size, char *str, char c, short b)
{
	char	**words;
	int		i;
	int		j;

	words = (char **) malloc(sizeof(char *) * (size->data + 1));
	!words && my_error(words, 0);
	size = size->next;
	i = -1;
	while (size)
	{
		words[++i] = (char *) malloc(sizeof(char) * (size->data + 1));
		!words[i] && my_error(words, i);
		j = 0;
		while (*str != c && *str)
			words[i][j++] = *str++;
		words[i][j] = '\0';
		if (*str)
			str++;
		while (!b && *str && *str == c)
			str++;
		size = size->next;
	}
	words[++i] = NULL;
	return (words);
}

// b == 1 python split
char	**my_split(char *str, char c, short b/*, int *len*/)
{
	t_struct	*size;
	t_struct	*tmp;
	char		**words;

	if (!str)
		return (NULL);
	while (!b && *str && *str == c)
		str++;
	size = get_size(str, c, b);
	words = fill(size, str, c, b);
    // (*len) = size->data;
	while (size)
	{
		tmp = size->next;
		free (size);
		size = tmp;
	}
	
	return (words);
}