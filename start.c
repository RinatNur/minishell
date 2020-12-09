#include "minishell.h"


int     main(int ac, char **av, char **envp) {
    t_data      data;
	t_list  	*list;
	t_list  	*sort_l;
	char		*command = "ls";
	char*		arr[] = { command, NULL, NULL };

//	data.conv = ft_ls

    list = NULL;
    data.ar = arr;
    make_env_list(&data, (const char **)envp);
//    check_command(&data);

    int		fd[2];
    int		pid1, pid2;

    pipe(fd);
    pid1 = fork();

    if (pid1 == 0)
	{
    	dup2(fd[1], STDOUT_FILENO);
    	close(fd[0]);
    	close(fd[1]);
		check_command(&data);
	}

    pid2 = fork();
    write (1, "hello", 5);
	if (pid2 == 0)
	{
		command = "cat";
		data.ar[0] = command;
		data.ar[1] = "-e";
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		check_command(&data);
	}
////
//    waitpid(pid1, NULL, 0);
//    waitpid(pid2, NULL, 0);
//	close(fd[0]);
//	close(fd[1]);


//    print_list(data.env_list);
//    while (env[i])
//	{
//    	j = 0;
//    	while (env[i][j])
//		{
//    		write(1, &env[i][j], 1);
//    		j++;
//		}
//    	write(1, "\n", 1);
//    	i++;
//	}
//	print_list(data.env_list);

//    command = "export";
//    data.ar[0] = command;
//    data.ar[1] = NULL;
//    check_command(&data);
//	write(1, "\n", 1);
////
//    command = "unset";
//    data.ar[0] = command;
//    data.ar[1] = "a";
//    data.ar[2] = "b";
//    data.ar[3] = NULL;
//    check_command(&data);
//	print_list(data.env_list);

//
//    write(1, "\n\n\n", 3);
//    command = "export";
//    data.ar[0] = command;
//    data.ar[1] = NULL;
//    check_command(&data, command, env);
    return(0);
}