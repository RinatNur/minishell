#include "parser/parse.h"
#include "functional/processing.h"

//TODO Roma
//FIXME unset PATH; echo $PATH
//FIXME ;       ;

//TODO Rinat

void		ft_pipe_eof(void)
{
	int mas[2];

	pipe(mas);
	write(mas[1], "", 0);
	dup2(mas[0], 0);
	close(mas[1]);
//	close(mas[0]);
}

void	handler_signals(int sig)
{
	if (sig == SIGINT)
	{
		ft_write(1, "\b\b  \b\b");
		ft_write(1, "\nminishell #> ");
		g_code = 1;
	}
	else
		ft_write(1, "\b\b  \b\b");
}

void		init_data(t_data *data, t_list **command, t_command **com)
{
	*com = ((t_command *)((*command)->content));
	data->redirect_list = (*com)->redirect_list;

	process_command_envs((*com)->command_with_arguments, data);
	process_redirect_envs((*com)->redirect_list, data);

	data->ar = (*com)->command_with_arguments;
}

static void process_command(t_data *data, char *command_line)
{
	t_list *pipeline_list;
	t_list *pipeline;
	t_list *command_list;
	t_list *command;
	t_command *com;

	data->redir_flag = 0;
	data->redir_pipe_flag = 0;
	data->fd_start[0] = dup(0);
	data->fd_start[1] = dup(1);
	pipeline_list = parse_pipeline_list(command_line);
	pipeline = pipeline_list;

	while (pipeline != NULL)
	{
		command_list = pipeline->content;
		command = command_list;
		while (command != NULL)
		{
			com = ((t_command *)(command->content));
			if (com->parse_error != NULL)
            {
                ft_error(com->parse_error, 2);
                command = command->next;
                continue;
            }
			data->redirect_list = com->redirect_list;
			process_command_envs(com->command_with_arguments, data);
			process_redirect_envs(com->redirect_list, data);

			data->ar = com->command_with_arguments;
			if (data->redirect_list && !command->next)
				ft_check_redirects(data, command);
			else if (!data->redirect_list && command->next)
				ft_pipe(data);
			else if (data->redirect_list && command->next)
			{
				if ((ft_check_redirects(data, command)) == 1)
				{
					command = command->next;
					continue;
				}
				if (data->redir_pipe_flag && data->redir_flag)
				{
					command = command->next;
					init_data(data, &command, &com);
					check_command(data);
				}
				else
					ft_pipe(data);
			}
			else
			{
				if (data->redir_pipe_flag || data->redir_flag)
					ft_pipe_eof();
				check_command(data);
			}
			command = command->next;
		}
		dup2(data->fd_start[0], 0);//to return fd 0 back;
		dup2(data->fd_start[1], 1);//to return fd 1 back;
		pipeline = pipeline->next;
	}
	free_pipeline_list(pipeline_list);
}
void loop(t_data *data)
{
	int flag;
	flag = 1;
	while (flag > 0)
	{
		write(1, "minishell #> ", 13);
		if (!(flag = get_next_line(0, &g_buf)))
		{
			ft_write(1, " exit\n");
			exit(0);
		}
		if (g_buf)
			process_command(data, g_buf);
		signal(SIGINT, handler_signals);
		signal(SIGQUIT, handler_signals);
		signal(SIGTERM, handler_signals);
		free(g_buf);
		free_env_list(data->env_list);//FIXME test
	}
}


int main(int ac, char **av, char **envp)
{
	t_data		data;

	g_code = 0;
	g_buf = NULL;
	make_env_list(&data, (const char **)envp);
	signal(SIGINT, handler_signals);
	signal(SIGQUIT, handler_signals);
	signal(SIGTERM, handler_signals);
	loop(&data);
	return (g_code);
}
