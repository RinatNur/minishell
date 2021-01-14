/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:54:11 by jheat             #+#    #+#             */
/*   Updated: 2021/01/14 17:54:13 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parse.h"
#include "functional/processing.h"

void			ft_pipe_eof(void)
{
	int mas[2];

	pipe(mas);
	write(mas[1], "", 0);
	dup2(mas[0], 0);
	close(mas[1]);
}

void			handler_signals(int sig)
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

static char		**arr_dup(char **arr)
{
	char		**result;
	int			i;

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

int				init_data_ar(t_data *data, t_list **command, t_command **com)
{
	*com = ((t_command *)((*command)->content));
	if ((*com)->parse_error != NULL)
	{
		ft_error((*com)->parse_error, 258);
		*command = (*command)->next;
		return (1);
	}
	data->redirect_list = (*com)->redirect_list;
	process_command_envs((*com)->command_with_arguments, data);
	process_redirect_envs((*com)->redirect_list, data);
	data->ar = arr_dup((*com)->command_with_arguments);
	return (0);
}

void			init_data_main(t_data *data)
{
	data->redir_flag = 0;
	data->redir_pipe_flag = 0;
	data->fd_start[0] = dup(0);
	data->fd_start[1] = dup(1);
}
