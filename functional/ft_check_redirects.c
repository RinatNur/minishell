/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redirects.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 17:00:05 by jheat             #+#    #+#             */
/*   Updated: 2021/01/12 17:00:10 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

static void			init_values(t_data *data)
{
	data->wr_file_name = NULL;
	data->rd_file_name = NULL;
	data->redir_pipe_flag = 0;
	data->redir_flag = 0;
}

static int			redirect_in_simple_and_rewrite(t_data *data)
{
	int		file;
	DIR		*check_if_dir;

	check_if_dir = opendir(REDIR->filename);
	file = open(REDIR->filename, O_WRONLY | O_CREAT, 0666);
	if (check_if_dir)
	{
		ft_error_print(MSHELL, REDIR->filename, NULL, ERR3);
		data->redir_flag = 1;
		return (1);
	}
	if (file == -1)
	{
		ft_error_print(MSHELL, REDIR->filename, NULL, ERR5);
		data->redir_flag = 1;
		return (1);
	}
	data->wr_file_name = REDIR->filename;
	data->wr_type_redir = REDIR->redirect_type;
	close(file);
	return (0);
}

static int			redirect_from(t_data *data)
{
	int		file;
	DIR		*check_if_dir;

	check_if_dir = opendir(REDIR->filename);
	file = open(REDIR->filename, O_RDONLY, 0666);
	if (check_if_dir)
	{
		ft_error_print(NULL, data->ar[0], "stdin", ERR3);
		data->redir_flag = 1;
		return (1);
	}
	if (file == -1)
	{
		(errno == 2) ? ft_error_print(MSHELL, REDIR->filename, NULL, ERR1)
		: ft_error_print(MSHELL, REDIR->filename, NULL, ERR5);
		data->redir_pipe_flag = 1;
		return (1);
	}
	data->rd_file_name = REDIR->filename;
	close(file);
	return (0);
}

int					ft_check_redirects(t_data *data, t_list *command)
{
	init_values(data);
	if (!data->redirect_list)
		return (1);
	while (data->redirect_list)
	{
		if (REDIR->redirect_type == into_file
			|| REDIR->redirect_type == into_file_with_rewrite)
		{
			if ((redirect_in_simple_and_rewrite(data)) == 1)
				return (1);
		}
		else
		{
			if ((redirect_from(data)) == 1)
				return (1);
		}
		data->redirect_list = data->redirect_list->next;
	}
	if (command->next && data->rd_file_name)
		ft_redirect_read_pipe(data);
	else
		ft_redirect_read(data);
	ft_redirect_write(data);
	data->redir_flag = 1;
	return (0);
}
