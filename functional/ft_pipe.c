#include "processing.h"

void 	ft_pipe(t_data *data)
{
	int			fd[2];
	pid_t		pid;
	int 		status = 0;

//	ft_pipe_eof();
	pipe(fd);
	pid = fork();

	if (pid == 0)
	{
//		if
//			ft_pipe_eof();
		dup2(fd[1], 1);
		check_command(data);
		exit(0);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		waitpid(pid, &status, WUNTRACED);
	}
}
