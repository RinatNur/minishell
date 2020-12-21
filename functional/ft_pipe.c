#include "processing.h"

void 	ft_pipe(t_data *data)
{
	int			fd[2];
	pid_t		pid;
	int 		status = 0;
//	char 		line[100];
//	ssize_t 	tmp;
	pipe(fd);
	pid = fork();

	if (pid == 0)
	{
		dup2(fd[1], 1);
//		tmp = read(fd[1], line, 50);
//		ft_putendl_fd(line, 1);
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
