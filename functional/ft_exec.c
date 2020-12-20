#include "processing.h"

void        check_command(t_data *data)
{
	char 	*com;

	com = data->ar[0];
	if (!com)
		return;
    if (!ft_strncmp("pwd", com, 4) || !ft_strncmp("PWD", com, 4))
        ft_pwd();
    else if (!ft_strncmp("echo", com, 5) || !ft_strncmp("ECHO", com, 5))
        ft_echo(data);
    else if (!ft_strncmp("cd", com, 3) || !ft_strncmp("CD", com, 3))
        ft_cd(data);
    else if (!ft_strncmp("export", com, 7))
        ft_export(data);
    else if (!ft_strncmp("unset", com, 6))
        ft_unset(data);
    else if (!ft_strncmp("env", com, 4))
        ft_env(data);
    else if (!ft_strncmp("exit", com, 5))
        ft_exit(data);
    else
        ft_exec(data);
}

char 	**list_to_mas_ref(t_data *data)
{
	t_env		*list;
	char 			**env;
	int 			i = 0;

	list = data->env_list;
	env = malloc(sizeof(char *) * (ft_lstsize_env(list) + 1));
	while (list)
	{
		env[i] = ft_strjoin(list->key, ft_strjoin("=", list->value));
		i++;
		list = list->next;
	}
	return (env);
}

int    ft_exec(t_data *data)//, char *pat, char **arr, char **env)
{
    int     err;
    pid_t 	pid;
    char 	**env;
    int 	status;

    env = list_to_mas_ref(data);
    pid = fork();
    if (pid == -1)
        return (1);
    if(pid == 0)
    {
//    	write(1, "hello", 5);
        err = execve(ft_find_path(data, data->ar[0]), data->ar, env);

//        g_err = errno;
        if (err == -1)
        	exit(WEXITSTATUS(err));
//        {
//            ft_write(1, "EXECVE return -1");
//            ft_write(1, "\n");
//			return (errno);
//        }

    }
    else
    {
        int     wait_status;
        int 	test;
		wait(&wait_status);
//		test = WEXITSTATUS(wait_status);
		int i = 0;
//		char *str = strerror(test);
//		while (i < 200)
//		{
//			ft_error_print(MSHELL, ft_itoa(i), NULL, str );
//			i++;
//		}
//		int i = 0;
//            int status_code = WEXITSTATUS(wait_status);
//        if (WIFEXITED(wait_status))
//        {
            int status_code = WEXITSTATUS(wait_status);
//            if (status_code == 0)
//                ft_write(1, "sucess");
//            else
//			{
//            	ft_write(2, "sdfgfdg");
//                printf("failure with the status code %d\n", status_code);

//			}
//        }
    }
    return (0);
}
