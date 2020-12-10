#include <minishell.h>

void 	ft_pipe(t_data *data)
{
	int			fd[2];
	pid_t		pid;
	int 		status = 0;

	pipe(fd);
	pid = fork();

	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		check_command(data);
		exit(0);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
//		command = "cat";
		waitpid(pid, &status, WUNTRACED);
//		check_command(data);
//		exit(0);
	}
//		data->ar[0] = "cat";
//		data->ar[1] = "-e";
//		data->ar[1] = NULL;
//		check_command(data);
//
//	waitpid(pid2, NULL, 0);
//	close(fd[0]);
//	close(fd[1]);
}
