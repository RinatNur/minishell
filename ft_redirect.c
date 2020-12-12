#include "minishell.h"

void		ft_redirect(t_data *data)
{
	pid_t		pid;
	int 		status = 0;
	int 		file;

	pid = fork();

	if (pid == 0)
	{
		file = open("test.txt", O_WRONLY | O_CREAT, 0777);
		dup2(file, 1);
//		close(fd[0]);
//		close(fd[1]);
		check_command(data);
		exit(0);
	}
	else
	{
//		file = open("test.txt", O_WRONLY | O_CREAT, 0777);
		dup2(fd[0], 0);
//		close(fd[1]);
//		close(fd[0]);
		waitpid(pid, &status, WUNTRACED);
//		exit(0);
	}
}

