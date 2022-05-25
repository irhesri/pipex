#include "pipex.h"

void	print_2D(char **s)
{
	while (*s)
	{
		fprintf(stderr, "%s\n", *s);
		s++;
	}
	
}