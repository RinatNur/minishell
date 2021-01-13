/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:29:08 by jheat             #+#    #+#             */
/*   Updated: 2021/01/13 18:29:11 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

void		ft_pipe(t_data *data)
{
	pid_t		pid;
	int			fd[2];
	int			status;

	status = 0;
	pipe(fd);
	pid = fork();
	if (pid == -1)
		ft_error_stderr(strerror(errno), 15);
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		check_command(data);
		exit(errno);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		waitpid(pid, &status, WUNTRACED);
	}
}
