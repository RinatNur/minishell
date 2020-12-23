#include "processing.h"

void		ft_redirect_read_pipe(t_data *data)
{
	pid_t		pid;
	int 		status = 0;
	int 		file;
	int 		argument;
	int 		fd[2];

	if (data->rd_file_name)
	{													//if >					if >>
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			file = open(data->rd_file_name, O_RDONLY, 0666);
			dup2(file, 0);
			dup2(fd[1], 1);
			close(fd[1]);
			close(fd[0]);
			if (data->wr_file_name)
			{
				argument = (data->wr_type_redir == into_file) ? O_WRONLY : (O_WRONLY | O_APPEND);
				file = open(data->wr_file_name, argument, 0666);
				dup2(file, 1);
			}
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
}

void		ft_redirect_read(t_data *data)
{
	pid_t		pid;
	int 		status = 0;
	int 		file;
	int 		argument;

	if (data->rd_file_name)
	{													//if >					if >>
		pid = fork();
		if (pid == 0)
		{
			file = open(data->rd_file_name, O_RDONLY, 0666);
			dup2(file, 0);
			if (data->wr_file_name)
			{
				argument = (data->wr_type_redir == into_file) ? O_WRONLY : (O_WRONLY | O_APPEND);
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


void		ft_redirect_write(t_data *data)
{
	pid_t		pid;
	int 		status = 0;
	int 		file;
	int 		argument;

	if (data->wr_file_name && !data->rd_file_name)
	{													//if >					if >>
		argument = (data->wr_type_redir == into_file) ? O_WRONLY : (O_WRONLY | O_APPEND);
		pid = fork();
		if (pid == 0)
		{
			file = open(data->wr_file_name, argument, 0666);
			dup2(file, 1);
			check_command(data);
			exit(errno);
		}
		else
		{
			waitpid(pid, &status, WUNTRACED);
		}
	}
}

