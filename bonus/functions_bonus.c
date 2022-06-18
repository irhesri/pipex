/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:19:38 by irhesri           #+#    #+#             */
/*   Updated: 2022/05/28 17:58:11 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*my_strjoin(char *str1, char *str2, short b)
{
	char	*str;
	int		i;

	str = (char *) malloc(ft_strlen(str1) + ft_strlen(str2) + 2);
	i = 0;
	while (str1 && *str1)
		str[i++] = *str1++;
	if (b)
		str[i++] = '/';
	while (str2 && *str2)
		str[i++] = *str2++;
	str[i] = '\0';
	return (str);
}

char	*its_path(char *str)
{
	if (!access(str, F_OK))
	{
		if (!access(str, X_OK))
			return (str);
		my_putstr(str, 2);
		error(": Permission denied", 126, 1);
	}
	my_putstr(str, 2);
	error(": command not found", 127, 1);
	return (NULL);
}

//	HANDLE ERRORS
char	*get_path(t_data *data, char *str, char *arg)
{
	char	*path;
	char	**paths;

	paths = data->paths;
	if (str && *str && (my_strch(str, '/') || !paths))
		return (its_path(str));
	while (str && *str && paths && *paths)
	{
		path = my_strjoin(*paths, str, **paths != '\0');
		if (!access(path, F_OK))
		{
			if (!access(path, X_OK))
				return (path);
			my_putstr(arg, 2);
			error(": Permission denied", 126, 1);
		}
		free (path);
		paths++;
	}
	my_putstr(arg, 2);
	error(": command not found", 127, 1);
	return (NULL);
}

void	open_files(t_data *data, char **av, int ac)
{
	int	mode;

	mode = O_APPEND;
	if (!my_strncmp(av[1], "here_doc", 9))
		data->fd[0] = 0;
	else
	{
		data->fd[0] = open(av[1], O_RDONLY);
		(data->fd[0] < 0) && error(av[1], 0, 0);
		mode = O_TRUNC;
	}
	data->fd[1] = open(av[ac - 1], O_CREAT | mode | O_WRONLY, 0644);
	(data->fd[1] < 0) && error(av[ac - 1], 0, 0);
}

void	get_data(t_data *data, int ac, char **av, char **env)
{
	int	i;

	i = -1;
	data->last_id = malloc(sizeof(pid_t));
	*(data->last_id) = 0;
	data->paths = NULL;
	data->env = env;
	while (env && *env && my_strncmp(*env, "PATH=", 5))
		env++;
	if (env && *env)
		data->paths = my_split(*env + 5, ':', 1);
	open_files(data, av, ac);
	av[ac - 1] = NULL;
	data->commands = av + 2;
	data->cmd = 0;
	data->size = ac - 3;
}
