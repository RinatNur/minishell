#include "processing.h"

void 	ft_pipe(t_data *data)
{
	int			fd[2];
	pid_t		pid;
	int 		status = 0;

	pipe(fd);
	pid = fork();
	if (pid == -1)
		ft_error_stderr(strerror(errno), 15);
	if (pid != 0)//TODO ==
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
