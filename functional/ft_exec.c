/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 20:55:06 by jheat             #+#    #+#             */
/*   Updated: 2021/01/13 20:55:09 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"
#include "./utils/utils.h"

int			status_return(int status)
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

int			check_exec(t_data *data, char *args)
{
	struct stat		buf;

	(stat(args, &buf)) ? buf.st_mode = 0 : 0;
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

static void 		parent_process_exec(char **env, char *path, int status, pid_t pid)
{
	if (pid > 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, WUNTRACED);
		g_code = status_return(status);
		free_arr(env);
		free(path);
	}
}

void		ft_exec(t_data *data)
{
	pid_t 	pid;
	char 	**env;
	int 	status;
	char	*path;
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	status = 0;
	if (!check_exec(data,data->ar[0]))
	{
		free(pwd);
		return;
	}
	if ((!(ft_strncmp("/", pwd, 2))
	&& (find_char(data->ar[0], '/')) >= 0)
	|| (!ft_strncmp("/", data->ar[0], 1)))
		path = ft_strdup(data->ar[0]);
	else
		path = ft_find_path(data, data->ar[0]);
	free(pwd);
	if(!(ft_strncmp("", path, 1)))
	{
		free(path);
		return;
	}
	env = list_to_mas_ref(data);
	pid = fork();
	if (pid == -1)
		ft_error_stderr(strerror(errno), 15);
	if(pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTERM, SIG_DFL);
		execve(path, data->ar, env);
		exit(g_code);
	}
	parent_process_exec(env, path, status, pid);
}
