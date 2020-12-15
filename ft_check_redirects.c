#include "minishell.h"

void 		ft_error_print(char *command, char *file, char *message)
{
	ft_write(1, command);
	ft_write(1, ": ");
	ft_write(1, file);
	ft_write(1, ": ");
	ft_write(1, message);
	ft_write(1, "\n");
}

int		ft_check_redirects(t_data *data)
{
	int 	file;
	DIR    *check_if_dir;

	if (!data->redirect_list)
		return (1);
	while (data->redirect_list)
	{
		if (REDIR->redirect_type != from_file)
		{
			if ((check_if_dir = opendir(REDIR->filename)))
			{
				ft_error_print("minishell", REDIR->filename, "Is a directory");
				return (1);
			}
			if ((file = open(REDIR->filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
			{
				ft_error_print("minishell", REDIR->filename, "Permission denied");
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
				ft_error_print(data->ar[0], "stdin", "Is a directory");
				return (1);
			}
			if ((file = open(REDIR->filename, O_RDONLY, 0666)) == -1)
			{
				(errno == 2) ? ft_error_print("minishell", REDIR->filename, "No such file or directory")
					: ft_error_print("minishell", REDIR->filename, "Permission denied");;
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
	return (0);
}