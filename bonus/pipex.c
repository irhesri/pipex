#include "pipex.h"

void	run_command(t_data *data, int *pipe1, int *pipe2, short b)
{
	pid_t	id;
	char	**command;
	char	*path;

	id = fork();
	if (b)
		*(data->last_id) = id;
	if (!id)
	{
		(pipe1[1] > 0) && close(pipe1[1]);
		(pipe2[0] > 0) && close(pipe2[0]);
		(dup2(pipe1[0], 0) == -1) && error(NULL, errno, 1);
		(dup2(pipe2[1], 1) == -1) && error(NULL, errno, 1);
		close(pipe1[0]);
		close(pipe2[1]);
		command = my_split(data->commands[data->cmd], ' ', 0);
		path = get_path(data, *command);
		execve(path, command, NULL);
		error(NULL, errno, 1);
	}
	close (pipe1[0]);
	close (pipe2[1]);
}

void	its_here_hoc(t_data *data, int *pipe1, int *pipe2)
{
	int		id;
	int		len;
	char	*str;

	str = NULL;
	len = ft_strlen(*data->commands);
	id = fork();
	if (!id)
	{
		close (pipe1[0]);
		while (my_strncmp(*data->commands, str, len))
		{
			str && my_putstr(str, pipe1[1]);
			str && my_putstr("\n", pipe1[1]);
			str = get_next_line(0);
		}
		close(pipe1[1]);
		exit (0);
	}
	wait (NULL);
	close (pipe1[1]);
	data->commands++;
	run_command(data, pipe1, pipe2, 0);
	data->commands--;
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	int		n;

	data = (t_data *) malloc(sizeof(t_data));
	get_data(data, ac, av, env);
	if (data->fd[0] > 0)
		run_command(data, data->fd, data->p[data->cmd], 0);
	else if (!data->fd[0])
	{
		its_here_hoc(data, data->p[data->cmd], data->p[data->cmd + 1]);
		data->cmd++;
	}
	else
		close (data->p[data->cmd][1]);
	while (++(data->cmd) < data->size - 1)
		run_command(data, data->p[data->cmd - 1], data->p[data->cmd], 0);
	if (data->fd[1] > 0 && data->cmd - 1 < data->size)
		run_command(data, data->p[data->cmd - 1], data->fd, 1);
	else
		close (data->p[data->cmd - 1][0]);
	n = wait_for_child(data);
	exit (n);
}
