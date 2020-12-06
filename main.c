#include "minishell.h"


int     main(int ac, char **av, char **envp) {
    t_data      data;
	t_list  	*list;
	t_list  	*sort_l;
	t_sort_env  sort_env;
	char		*pwd;
	int			pid;
	int			size_of_env;
	char		**env_start;
	char		**env = NULL;
	int			i = 0, j;
	char		*path;
	char		*command = "export";
	char*		arr[] = { command, "a", "123", "b", "456", NULL };



    list = NULL;
    data.ar = arr;
//    env_start = env_copy(&data, (const char **)envp);
    make_env_list(&data, (const char **)envp);
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
    check_command(&data);
	print_list(data.env_list);

//    command = "pwd";
//    data.ar[0] = command;
//    data.ar[1] = NULL;
//    check_command(&data);
//
    command = "unset";
    data.ar[0] = command;
    data.ar[1] = "a";
    data.ar[2] = "b";
    data.ar[3] = NULL;
    check_command(&data);
	print_list(data.env_list);

//
//    write(1, "\n\n\n", 3);
//    command = "export";
//    data.ar[0] = command;
//    data.ar[1] = NULL;
//    check_command(&data, command, env);
    return(0);
}