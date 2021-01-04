#include "processing.h"

void 		get_g_code(char *message, char *command)
{
	if (!(ft_strncmp(ERR2, message, (ft_strlen(message) + 1))))
		g_code = 127;
	else if (!(ft_strncmp("env", command, 4))
		&& !(ft_strncmp(ERR1, message, (ft_strlen(ERR1) + 1))))
		g_code = 127;
	else if (!(ft_strncmp(ERR1, message, (ft_strlen(ERR1) + 1))))
		g_code = 1;
	else if (!(ft_strncmp(ERR3, message, (ft_strlen(ERR3) + 1))))
		g_code = 1;
	else if (!(ft_strncmp(ERR4, message, (ft_strlen(ERR4) + 1))))
		g_code = 1;
	else if (!(ft_strncmp(ERR5, message, (ft_strlen(ERR5) + 1))))
		g_code = 1;
	else if (!(ft_strncmp(ERR6, message, (ft_strlen(ERR6) + 1))))
		g_code = 1;
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
	get_g_code(message, command);
//	exit(g_code);
}

void    ft_error(char *str, int code)
{
    ft_write (2, str);
    ft_write (2, "\n");
//    exit (code);
}

void 	ft_error_stderr(char *str, int code)
{
	ft_putendl_fd(str, 2);
	exit(code);
}
