/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irhesri <irhesri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 10:19:48 by irhesri           #+#    #+#             */
/*   Updated: 2022/05/28 15:10:19 by irhesri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <limits.h>

typedef struct s_data
{
	char	**paths;
	char	**commands;
	char	**env;
	int		size;
	int		cmd;
	int		fd[2];
	pid_t	*last_id;
}	t_data;

void	get_data(t_data *data, int ac, char **av, char **env);
char	*get_path(t_data *data, char *str, char *arg);
// char	*get_path(t_data *data, char *str);
int		wait_for_child(t_data *data);
short	error(char *str, int err, short b);
char	*get_next_line(int fd);
char	**my_split(char *str, char c, short b);
short	my_strncmp(char *str1, char *str2, int n);
short	my_putstr(char *str, int fd);
size_t	ft_strlen(char *str);
short	my_strch(char *str, char c);

#endif
