#include "minishell.h"

void        check_command(t_data *data)
{
    if (!ft_strncmp("pwd", data->ar[0], 4))
        ft_pwd();
    else if (!ft_strncmp("echo", data->ar[0], 5))
        ft_echo(data);
    else if (!ft_strncmp("cd", data->ar[0], 3))
        ft_cd(data);
    else if (!ft_strncmp("export", data->ar[0], 7))
        ft_export(data);
    else if (!ft_strncmp("unset", data->ar[0], 6))
        ft_unset(data);
    else if (!ft_strncmp("env", data->ar[0], 4))
        ft_env(data);
    else if (!ft_strncmp("exit", data->ar[0], 5))
        ft_exit(data);
    else
        ft_exec(data);
}

char 	**list_to_mas_ref(t_data *data)
{
	t_list		*list;
	char 			**env;
	int 			i = 0;

	list = data->env_list;
	env = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
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
    int     pid, err;
    char 	**env;

    env = list_to_mas_ref(data);
    pid = fork();
    if (pid == -1)
        return (1);
    if(pid == 0)
    {
//    	write(1, "hello", 5);
        err = execve(ft_find_path(data, data->ar[0]), data->ar, env);
        if (err == -1)
        {
            printf("FAILURE\n");
            return (err);
        }

    }
//    else
//    {
//        int     wait_status = 0;
//        wait (&wait_status);
//        if (WIFEXITED(wait_status))
//        {
//            int status_code = WEXITSTATUS(wait_status);
//            if (status_code == 0)
//                printf("sucess");
//            else
//                printf("failure with the status code %d\n", status_code);
//        }
//     }
    return (0);
}
