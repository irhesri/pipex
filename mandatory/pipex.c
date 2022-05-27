/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:18:35 by irhesri           #+#    #+#             */
/*   Updated: 2022/05/27 10:34:55 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		path = get_path(data, *command, data->commands[data->cmd]);
		execve(path, command, data->env);
		error(NULL, errno, 1);
	}
	close (pipe1[0]);
	close (pipe2[1]);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	int		p[2];
	int		n;

	if (ac != 5)
		error("usage: input cmd1 cmd2 output", 1, 1);
	data = (t_data *) malloc(sizeof(t_data));
	get_data(data, ac, av, env);
	data->env = env;
	(pipe(p) == -1) && error(NULL, errno, 1);
	if (data->fd[0] > 0)
		run_command(data, data->fd, p, 0);
	else
		close(p[1]);
	data->cmd++;
	if (data->fd[1] > 0)
		run_command(data, p, data->fd, 1);
	else
		close (p[0]);
	n = wait_for_child(data);
	exit (n);
}
