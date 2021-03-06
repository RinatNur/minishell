/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:46:48 by jheat             #+#    #+#             */
/*   Updated: 2021/01/14 17:32:40 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parse.h"
#include "functional/processing.h"

static int		do_if_redirects_and_pipes_in_line(t_data *data,
								t_list **command, t_command **com)
{
	if ((ft_check_redirects(data, *command)) == 1)
	{
		*command = (*command)->next;
		free_2d_array(data->ar);
		return (1);
	}
	if (data->redir_pipe_flag && data->redir_flag)
	{
		*command = (*command)->next;
		free_2d_array(data->ar);
		if ((init_data_ar(data, &(*command), &(*com))) == 1)
			return (1);
		check_command(data);
	}
	else
		ft_pipe(data);
	return (0);
}

static int		process_command(t_data *data, t_list **command)
{
	t_command *com;

	if ((init_data_ar(data, &(*command), &com)) == 1)
		return (1);
	if (data->redirect_list && !(*command)->next)
		ft_check_redirects(data, *command);
	else if (!data->redirect_list && (*command)->next)
		ft_pipe(data);
	else if (data->redirect_list && (*command)->next)
	{
		if ((do_if_redirects_and_pipes_in_line(data, &(*command), &com)) == 1)
			return (1);
	}
	else
	{
		if (data->redir_pipe_flag || data->redir_flag)
			ft_pipe_eof();
		check_command(data);
	}
	free_2d_array(data->ar);
	*command = (*command)->next;
	return (1);
}

static void		process_pipeline(t_data *data, char *command_line)
{
	t_list *pipeline_list;
	t_list *pipeline;
	t_list *command_list;
	t_list *command;

	init_data_main(data);
	pipeline_list = parse_pipeline_list(command_line);
	pipeline = pipeline_list;
	while (pipeline != NULL)
	{
		command_list = pipeline->content;
		command = command_list;
		while (command != NULL)
		{
			if ((process_command(data, &command)) == 1)
				continue ;
		}
		dup2(data->fd_start[0], 0);
		dup2(data->fd_start[1], 1);
		pipeline = pipeline->next;
	}
	free_pipeline_list(pipeline_list);
}

void			loop(t_data *data)
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
			process_pipeline(data, g_buf);
		signal(SIGINT, handler_signals);
		signal(SIGQUIT, handler_signals);
		signal(SIGTERM, handler_signals);
		free(g_buf);
	}
}

int				main(int ac, char **av, char **envp)
{
	t_data		data;

	if (ac && av)
	{
	}
	g_code = 0;
	g_buf = NULL;
	make_env_list(&data, (const char **)envp);
	signal(SIGINT, handler_signals);
	signal(SIGQUIT, handler_signals);
	signal(SIGTERM, handler_signals);
	loop(&data);
	return (g_code);
}
