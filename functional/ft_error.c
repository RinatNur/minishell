/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:22:16 by jheat             #+#    #+#             */
/*   Updated: 2021/01/14 14:22:19 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

void		ft_error_print(char *minishell, char *command,
							char *filename, char *message)
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
	if (ERR2 != NULL && message != NULL
		&& !(ft_strncmp(ERR2, message, (ft_strlen(message) + 1))))
		g_code = 127;
	else if (command != NULL && !(ft_strncmp("env", command, 4))
			&& !(ft_strncmp(ERR1, message, (ft_strlen(ERR1) + 1))))
		g_code = 127;
	else
		g_code = 1;
}

void		ft_error(char *str, int code)
{
	ft_write(2, str);
	ft_write(2, "\n");
	g_code = code;
}

void		ft_error_stderr(char *str, int code)
{
	ft_putendl_fd(str, 2);
	exit(code);
}
