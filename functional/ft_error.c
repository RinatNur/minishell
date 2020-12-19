#include "processing.h"

<<<<<<< HEAD
void 		ft_error_print(char *minishell, char *command, char *filename, char *message)
{
	if (minishell)
	{
		ft_write(1, minishell);
		ft_write(1, ": ");
	}
	if (command)
	{
		ft_write(1, command);
		ft_write(1, ": ");
	}
	if (filename)
	{
		ft_write(1, filename);
		ft_write(1, ": ");
	}
	ft_write(1, message);
	ft_write(1, "\n");
}

void    ft_error(char *str, int code)
{
    ft_write (1, str);
    write (1, "\n", 1);
=======
void    ft_error(char *str, int code)
{
    write (1, str, ft_strlen((str)));
>>>>>>> origin/master
    exit (code);
}
