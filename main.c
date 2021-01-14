/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:46:48 by jheat             #+#    #+#             */
/*   Updated: 2021/01/14 14:46:52 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parse.h"
#include "functional/processing.h"

void		ft_pipe_eof(void)
{
	int mas[2];

	pipe(mas);
	write(mas[1], "", 0);
	dup2(mas[0], 0);
	close(mas[1]);
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

static char **arr_dup(char **arr)
{
	char **result;
	int i;

	i = 0;
	if (arr == NULL)
		return (NULL);
	while (arr[i] != NULL)
		i++;
	if (!(result = malloc(sizeof(char *) * (i + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (arr[i] != NULL)
	{
		result[i] = ft_strdup(arr[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}

void		init_data(t_data *data, t_list **command, t_command **com)
{
	*com = ((t_command *)((*command)->content));
	data->redirect_list = (*com)->redirect_list;

	process_command_envs((*com)->command_with_arguments, data);
	process_redirect_envs((*com)->redirect_list, data);

	data->ar = arr_dup((*com)->command_with_arguments);
}

static void init_data_main(t_data *data)
{
	data->redir_flag = 0;
	data->redir_pipe_flag = 0;
	data->fd_start[0] = dup(0);
	data->fd_start[1] = dup(1);
}

static void process_command(t_data *data, char *command_line)
{
	t_list *pipeline_list;
	t_list *pipeline;
	t_list *command_list;
	t_list *command;
	t_command *com;

	init_data_main(data);
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
			data->ar = arr_dup(com->command_with_arguments);
			if (data->redirect_list && !command->next)
				ft_check_redirects(data, command);
			else if (!data->redirect_list && command->next)
				ft_pipe(data);
			else if (data->redirect_list && command->next)
			{
				if ((ft_check_redirects(data, command)) == 1)
				{
					command = command->next;
					free_2d_array(data->ar);
					continue;
				}
				if (data->redir_pipe_flag && data->redir_flag)
				{
					command = command->next;
					free_2d_array(data->ar);
					com = ((t_command *)((*command).content));
					data->redirect_list = (*com).redirect_list;

					process_command_envs((*com).command_with_arguments, data);
					process_redirect_envs((*com).redirect_list, data);

					data->ar = arr_dup((*com).command_with_arguments);
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
			free_2d_array(data->ar);
			command = command->next;
		}
		dup2(data->fd_start[0], 0);
		dup2(data->fd_start[1], 1);
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
