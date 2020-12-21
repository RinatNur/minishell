#include "processing.h"

int		ft_check_redirects(t_data *data)
{
	int 	file;
	DIR    *check_if_dir;
	data->wr_file_name = NULL;
	data->rd_file_name = NULL;
//	data->wr_type_redir = -1;

	if (!data->redirect_list)
		return (1);
	while (data->redirect_list)
	{
		if (REDIR->redirect_type == into_file || REDIR->redirect_type == into_file_with_rewrite)
		{
			if ((check_if_dir = opendir(REDIR->filename)))
			{
				ft_error_print(MSHELL, NULL, REDIR->filename, "Is a directory");
				return (1);
			}
			if ((file = open(REDIR->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
			{
				ft_error_print(MSHELL, NULL, REDIR->filename, "Permission denied");
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
				ft_error_print(NULL,data->ar[0], "stdin", "Is a directory");
				return (1);
			}
			if ((file = open(REDIR->filename, O_RDONLY, 0666)) == -1)
			{
				(errno == 2) ? ft_error_print(MSHELL, NULL, REDIR->filename, "No such file or directory")
					: ft_error_print(MSHELL, NULL, REDIR->filename, "Permission denied");
				close(file);
				return (1);
			}
			data->rd_file_name = REDIR->filename;
		}
		data->redirect_list = data->redirect_list->next;
	}
	close(file);
	ft_redirect_read(data);
	ft_redirect_write(data);
	data->redir_flag = 1;
//	ft_p	ipe_eof();
//	write(0, "", 0);
//	dup2(1, 0);
	return (0);
}