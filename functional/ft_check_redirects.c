#include "processing.h"

int		ft_check_redirects(t_data *data, t_list *command)
{
	int 	file;
	DIR    *check_if_dir;
	data->wr_file_name = NULL;
	data->rd_file_name = NULL;
	data->redir_pipe_flag = 0;
	data->redir_flag = 0;
	t_list 	*flag_list;
//	data->wr_type_redir = -1;

	flag_list = data->redirect_list;
	if (!data->redirect_list)
		return (1);
	while (data->redirect_list)
	{
		if (REDIR->redirect_type == into_file || REDIR->redirect_type == into_file_with_rewrite)
		{
			if ((check_if_dir = opendir(REDIR->filename)))
			{
				ft_error_print(MSHELL, REDIR->filename, NULL, ERR3);
				data->redir_flag = 1;
				return (1);
			}
			if ((file = open(REDIR->filename, O_WRONLY | O_CREAT, 0666)) == -1)
			{
				ft_error_print(MSHELL, REDIR->filename, NULL, ERR5);
				data->redir_flag = 1;
				close(file);
				return (1);
			}
			data->wr_file_name = REDIR->filename;
			data->wr_type_redir = REDIR->redirect_type;
		}
		else
		{
			if ((check_if_dir = opendir(REDIR->filename)))
			{
				ft_error_print(NULL,data->ar[0], "stdin", ERR3);
				data->redir_flag = 1;
				return (1);
			}
			if ((file = open(REDIR->filename, O_RDONLY, 0666)) == -1)
			{
				(errno == 2) ? ft_error_print(MSHELL, NULL, REDIR->filename, ERR1)
					: ft_error_print(MSHELL, REDIR->filename,  NULL, ERR5);
				close(file);
				data->redir_pipe_flag = 1;//to enter in ft_pipe_eof in main.c
				return (1);
			}
			data->rd_file_name = REDIR->filename;
		}
		data->redirect_list = data->redirect_list->next;
	}
	close(file);
	if (command->next && data->rd_file_name)
		ft_redirect_read_pipe(data);
	else
		ft_redirect_read(data);
	ft_redirect_write(data);
	data->redir_flag = 1;
	return (0);
}