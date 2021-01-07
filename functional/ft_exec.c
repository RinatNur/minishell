#include "processing.h"
#include "../utils/utils.h"

void        check_command(t_data *data)
{
	static int	count = 0;
	char 	*com;

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
	char 			*tmp;

	list = data->env_list;
	env = malloc(sizeof(char *) * (ft_lstsize_env(list) + 1));
	while (list)
	{
		tmp = ft_strjoin("=", list->value);
		env[i] = ft_strjoin(list->key, tmp);
		i++;
		list = list->next;
		free(tmp);
	}
	return (env);
}

int     status_return(int status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
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
		{
			ft_write(2, "Terminated: 15\n");
			return (143);
		}
	}
	return (WEXITSTATUS(status));
}

int		check_exec(char *args)
{
	struct stat		buf;

	buf.st_mode = 0;
	stat(args, &buf);
	if (buf.st_mode & S_IFREG)
	{
		if (!(buf.st_mode & S_IXUSR))
		{
			ft_error_print(MSHELL, args, NULL, ERR5);
			g_code = 126;
			return (0);
		}
	}
	else if (S_ISDIR(buf.st_mode))
	{
		ft_error_print(MSHELL, args, NULL, ERR31);
		g_code = 126;
		return (0);
	}
	else if (args[0] == '/' && (!(buf.st_mode & S_IFREG)))
	{
		ft_error_print(MSHELL, args, NULL, ERR1);
		g_code = 127;
		return (0);
	}
	return (1);
}


void    ft_exec(t_data *data)
{
	pid_t 	pid;
	char 	**env;
	int 	status;
	char	*path;

	status = 0;

	if (!check_exec(data->ar[0]))
		return ;
	env = list_to_mas_ref(data);
	if ((pid = fork()) == -1)
		ft_error_stderr(strerror(errno), 15);
	if(pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		path = ((find_char(data->ar[0], '/')) >= 0)
			   ? data->ar[0] : (ft_find_path(data, data->ar[0]));
		execve(path, data->ar, env);
		exit(g_code);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, WUNTRACED);
	g_code = status_return(status);
	free_arr(env);
}
