/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:36:37 by jheat             #+#    #+#             */
/*   Updated: 2021/01/13 18:36:39 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

static void		parent_process(int *fd, int status, pid_t pid)
{
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	waitpid(pid, &status, WUNTRACED);
}

static void		child_process(t_data *data, int *fd)
{
	int		argument;
	int		file;

	file = open(data->rd_file_name, O_RDONLY, 0666);
	dup2(file, 0);
	dup2(fd[1], 1);
	close(fd[1]);
	close(fd[0]);
	if (data->wr_file_name)
	{
		argument = (data->wr_type_redir == into_file)
					? O_WRONLY : (O_WRONLY | O_APPEND);
		file = open(data->wr_file_name, argument, 0666);
		dup2(file, 1);
	}
	check_command(data);
	exit(errno);
}

void			ft_redirect_read_pipe(t_data *data)
{
	pid_t		pid;
	int			status;
	int			fd[2];

	status = 0;
	data->redir_pipe_flag = 1;
	if (data->rd_file_name)
	{
		pipe(fd);
		pid = fork();
		if (pid == -1)
			ft_error_stderr(strerror(errno), 15);
		if (pid == 0)
			child_process(data, fd);
		else
			parent_process(fd, status, pid);
	}
}

void			ft_redirect_read(t_data *data)
{
	pid_t		pid;
	int			status;
	int			file;
	int			argument;

	if (!(status = 0) && data->rd_file_name)
	{
		pid = fork();
		if (pid == 0)
		{
			file = open(data->rd_file_name, O_RDONLY, 0666);
			dup2(file, 0);
			if (data->wr_file_name)
			{
				argument = (data->wr_type_redir == into_file)
							? O_WRONLY : (O_WRONLY | O_APPEND);
				file = open(data->wr_file_name, argument, 0666);
				dup2(file, 1);
			}
			check_command(data);
			exit(errno);
		}
		else
			waitpid(pid, &status, WUNTRACED);
	}
}

void			ft_redirect_write(t_data *data)
{
	pid_t		pid;
	int			status;
	int			file;
	int			argument;

	status = 0;
	if (data->wr_file_name && !data->rd_file_name)
	{
		argument = (data->wr_type_redir == into_file)
					? O_WRONLY : (O_WRONLY | O_APPEND);
		pid = fork();
		if (pid == 0)
		{
			file = open(data->wr_file_name, argument, 0666);
			dup2(file, 1);
			check_command(data);
			exit(errno);
		}
		else
			waitpid(pid, &status, WUNTRACED);
	}
}
