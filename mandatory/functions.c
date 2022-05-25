#include "pipex.h"

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
char	*get_path(t_data *data, char *str)
{
	char	*path;
	char	**paths;
	short	n;

	paths = data->paths;
	if (my_strch(str, '/'))
		return (its_path(str));
	while (paths && *paths)
	{
		path = my_strjoin(*paths, str,
				**paths != '\0');
		if (!access(path, F_OK))
		{
			if (!access(path, X_OK))
				return (path);
			my_putstr(str, 2);
			error(": Permission denied", 126, 1);
		}
		free (path);
		paths++;
	}
	my_putstr(str, 2);
	error(": command not found", 127, 1);
	return (NULL);
}

void	get_data(t_data *data, int ac, char **av, char **env)
{
	data->last_id = malloc(sizeof(pid_t));
	*(data->last_id) = 0;
	data->paths = NULL;
	while (env && *env && strncmp(*env, "PATH=", 5))
		env++;
	if (env && *env)
		data->paths = my_split(*env + 5, ':', 1);
	data->fd[0] = open(av[1], O_RDONLY);
	(data->fd[0] < 0) && error(av[1], 0, 0);
	data->fd[1] = open(av[ac - 1], O_TRUNC | O_CREAT | O_WRONLY, 0644);
	(data->fd[1] < 0) && error(av[ac - 1], 0, 0);
	av[ac - 1] = NULL;
	data->commands = av + 2;
	data->cmd = 0;
	data->size = ac - 3;
}

int	wait_for_child(t_data *data)
{
	int	n;
	int	id;
	int	*status;

	status = malloc(sizeof(int));
	*status = 0;
	n = 0;
	id = -2;
	while (1)
	{
		id = waitpid(-1, status, 0);
		if (data->fd[1] < 0)
			n = 1;
		else if (id == *data->last_id)
		{
			if (WIFEXITED(*status))
				n = WEXITSTATUS(*status);
			else if (WIFSIGNALED(*status))
				n = 128 + WTERMSIG(*status);
		}
		if (id == -1)
			break ;
	}
	free (status);
	return (n);
}
