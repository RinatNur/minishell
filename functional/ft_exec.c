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

int     status_return(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
		{
			ft_write(1, "\n");
			return (130);
		}
		if (WTERMSIG(status) == 3)
		{
			ft_write(1, "Quit: 3\n");
			return (131);
		}
		if (WTERMSIG(status) == 15)
			return (143);
	}
	return (WEXITSTATUS(status));
}

int    ft_exec(t_data *data)//, char *pat, char **arr, char **env)
{
    int     err = 0;
    pid_t 	pid;
    char 	**env;
    int 	status;

    env = list_to_mas_ref(data);
    pid = fork();
    if (pid == -1)
		ft_error_stderr(strerror(errno), 15);
    if(pid == 0)
    {
		if(!(err = execve(ft_find_path(data, data->ar[0]), data->ar, env)))
		{
//			ft_error_print(MSHELL, data->ar[0], NULL, "ERR2");
//			g_code = 127;
			exit(WEXITSTATUS(err));
		}
	}
    else
    {
		waitpid(pid, &status, WUNTRACED);
		g_code = status_return(status);
    }
    return (0);
}
