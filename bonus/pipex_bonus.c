/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:20:09 by irhesri           #+#    #+#             */
/*   Updated: 2022/08/04 13:27:29 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	run_command(t_data *data, int *pipe2, short b)
{
	pid_t		id;
	char		**command;
	char		*path;
	static int	pipe1;

	if (!pipe1)
		pipe1 = data->fd[0];
	id = fork();
	*(data->last_id) = id;
	if (!id)
	{
		if (pipe1 < 0 || pipe2[1] < 0)
			exit (1);
		(b != 1) && close(pipe2[0]);
		(dup2(pipe1, 0) == -1) && error(NULL, errno, 1);
		(dup2(pipe2[1], 1) == -1) && error(NULL, errno, 1);
		close(pipe1);
		close(pipe2[1]);
		command = my_split(data->commands[data->cmd], ' ', 0);
		path = get_path(data, *command, data->commands[data->cmd]);
		execve(path, command, data->env) && error(NULL, errno, 1);
	}
	(pipe1 > 0) && close (pipe1);
	(pipe2[1] > 0) && close (pipe2[1]);
	pipe1 = pipe2[0];
}

void	its_here_hoc(t_data *data)
{
	int		id;
	int		len;
	char	*str;
	int		pipe1[2];

	len = ft_strlen(*data->commands);
	(pipe(pipe1) == -1) && error(NULL, errno, 1);
	id = fork();
	if (!id)
	{
		close (pipe1[0]);
		str = get_next_line(0);
		while (str
			&& (my_strncmp(*data->commands, str, len) || str[len] != '\n'))
		{
			my_putstr(str, pipe1[1]);
			free(str);
			str = get_next_line(0);
		}
		close(pipe1[1]);
		exit (0);
	}
	wait (NULL);
	close (pipe1[1]);
	data->fd[0] = pipe1[0];
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
		if (id == *data->last_id)
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

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	int		n;
	int		p[2];

	(ac < 5) && error("not enough arguments", 1, 1);
	data = (t_data *) malloc(sizeof(t_data));
	get_data(data, ac, av, env);
	(pipe(p) == -1) && error(NULL, errno, 1);
	if (!data->fd[0])
	{
		(ac < 6) && error("not enough arguments", 1, 1);
		its_here_hoc(data);
		data->cmd++;
	}
	run_command(data, p, 0);
	while (++(data->cmd) < (data->size - 2))
	{
		(pipe(p) == -1) && error(NULL, errno, 1);
		run_command(data, p, 0);
	}
	if (data->cmd - 1 < data->size)
		run_command(data, data->fd, 1);
	n = wait_for_child(data);
	exit (n);
}
