#include "processing.h"
#include "./utils/utils.h"

void 		print_arr(char **env)
{
	int i;
	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

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
	int 			i;
	size_t 			len;
	char 			*tmp;

	i = 0;
	env = NULL;
	tmp = NULL;
	list = data->env_list;
	len = ft_lstsize_env(list) + 1;
	if (!(env = (char **)malloc(sizeof(char *) * len)))
		ft_error_stderr("malloc: memory not allocated", errno);
	env[len - 1] = NULL;
	while (list)
	{
		if (list->value)
		{
			tmp = ft_strjoin("=", list->value);
			env[i] = ft_strjoin(list->key, tmp);
			free(tmp);
		}
		else
			env[i] = ft_strdup(list->key);

		ft_write(1, env[i]);
		ft_write(1,"\n");
		i++;
		list = list->next;
	}
//	print_arr(env);
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

int		check_exec(t_data *data, char *args)
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

	if (!check_exec(data,data->ar[0]))
		return ;
	env = list_to_mas_ref(data);
	if ((pid = fork()) == -1)
		ft_error_stderr(strerror(errno), 15);
	if(pid == 0)//TODO ==
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		if ((!(ft_strncmp("/", get_value_from_env(data, "PWD"), 2))
			&& (find_char(data->ar[0], '/')) >= 0)
			|| (!ft_strncmp("/", data->ar[0], 1)))
			path = data->ar[0];
		else
			path = ft_find_path(data, data->ar[0]);
		execve(path, data->ar, env);
		exit(g_code);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, WUNTRACED);
	g_code = status_return(status);
	free_arr(env);
}
