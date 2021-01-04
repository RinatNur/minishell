#include "processing.h"
#include "../utils/utils.h"

void        check_command(t_data *data)
{
	static int	count = 0;
	char 	*com;

//	if (count || (data->redir_flag || data->redir_pipe_flag))
	g_code = 0;
	count++;
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

void	handle_parent_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(0, "\b\b  \b\b", 6);
		write(0, "\n", 1);
		write(0, "minishell ->", ft_strlen("minishell ->"));
		g_code = 1;
	}
	else
		write(0, "\b\b  \b\b", 6);
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
		ft_error_stderr(strerror(errno), 15);
    if(pid == 0)
    {
    	if ((find_char(data->ar[0], '/')) >= 0)
		{
			status = execve(data->ar[0], data->ar, env);
			ft_error_print(MSHELL, data->ar[0], NULL, ERR2);
			exit(WEXITSTATUS(status));
		}
    	else
		{
			status = execve(ft_find_path(data, data->ar[0]), data->ar, env);
			ft_error_print(MSHELL, data->ar[0], NULL, ERR2);
			exit(WEXITSTATUS(status));
		}
	}
    else
    {
//		signal(SIGQUIT, SIG_IGN);
//		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, WUNTRACED);
//		signal(SIGQUIT, handle_parent_signal);
//		signal(SIGINT, handle_parent_signal);
//		waitpid(pid, &status, WUNTRACED);
//		int tmp1 = WIFEXITED(status);
//		int tmp = WEXITSTATUS(status);
		g_code = status_return(status);
    }
    return (0);
}
