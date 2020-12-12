#include "minishell.h"


int     main(int ac, char **av, char **envp) {
	t_conv		conv;
    t_data      data;
	char  	list[1000];
	t_list  	*sort_l;
	char		*command = "echo";
	char*		arr[] = { command, "New new new", NULL };
	int 		file;

	//TODO try to send conv to the pipe;
    data.ar = arr;
    make_env_list(&data, (const char **)envp);
//    list = get_value_from_env(&data, "PATH");
	ft_redirect(&data);
//	file = open("test.txt", O_WRONLY | O_CREAT, 0777);
//	ft_pipe(&data);

//	check_command(&data);
//	write(1, "sgasg", 9);
//	list[999] = '\0';
//	command = "grep";
//    data.ar[0] = command;
//    data.ar[1] = "test.txt";
//    data.ar[2] = NULL;

//	ft_pipe(&data);
//	ft_pipe(&data);
//	ft_pipe(&data);
//	ft_pipe(&data);
//	check_command(&data);
//    list = ft_find_path(&data, "ls");
//	!(list = get_value_from_env(&data, "PATHf")) ? ft_error("No environment variable found", 6) : 0;
//	ft_write(1, list);
//    printf("\n");
//	print_list(data.env_list);
//	printf("\n");
//exit(111);
//	data.conv = ft_ls

//    list = NULL;
////    check_command(&data);
//
//    int		fd[2];
//    int		pid1, pid2;
//
//    pipe(fd);
//    pid1 = fork();
//
//    if (pid1 == 0)
//	{
//    	dup2(fd[1], STDOUT_FILENO);
//    	close(fd[0]);
//    	close(fd[1]);
//		check_command(&data);
//	}
//	else
//	{
//		command = "cat";
//		data.ar[0] = command;
//		data.ar[1] = "-e";
//		dup2(fd[0], STDIN_FILENO);
//		close(fd[1]);
//		close(fd[0]);
//		check_command(&data);
//	}
//
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