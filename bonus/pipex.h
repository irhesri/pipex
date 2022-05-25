#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

typedef struct s_data
{
	char	**paths;
	char	**commands;
	int		size;
	int		**p;
	int		cmd;
	int		fd[2];
	pid_t	*last_id;
}	t_data;

void	get_data(t_data *data, int ac, char **av, char **env);
char	*get_path(t_data *data, char *str);
int		wait_for_child(t_data *data);
short	error(char *str, int err, short b);
char	*get_next_line(int fd);
char	**my_split(char *str, char c, short b);
short	my_strncmp(char *str1, char *str2, int n);
short	my_putstr(char *str, int fd);
size_t	ft_strlen(char *str);
short	my_strch(char *str, char c);

#endif