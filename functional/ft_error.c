#include "processing.h"

void 		get_g_code(char *message)
{
	if (!(ft_strncmp(ERR2, message, (ft_strlen(message) + 1))))
		g_code = 127;
}

void 		ft_error_print(char *minishell, char *command, char *filename, char *message)
{
	if (minishell)
	{
		ft_write(2, minishell);
		ft_write(2, ": ");
	}
	if (command)
	{
		ft_write(2, command);
		ft_write(2, ": ");
	}
	if (filename)
	{
		ft_write(2, filename);
		ft_write(2, ": ");
	}
	ft_write(2, message);
	ft_write(2, "\n");
	get_g_code(message);
}

void    ft_error(char *str, int code)
{
    ft_write (2, str);
    ft_write (2, "\n");
    exit (code);
}

void 	ft_error_stderr(char *str, int code)
{
	ft_putendl_fd(str, 2);
	exit(code);
}
