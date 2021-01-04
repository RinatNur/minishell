#include "parser/parse.h"
#include "functional/processing.h"

//TODO Roma
//FIXME process_export_arg exit(1) must be changed;

//TODO Rinat
//TODO g_code - nulling after cycle
//TODO exit | echo hello minishell write "exit"

void		ft_pipe_eof(void)
{
	int mas[2];

	pipe(mas);
	write(mas[1], "", 0);
	dup2(mas[0], 0);
	close(mas[1]);
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
			data->redirect_list = com->redirect_list;
			process_command_envs(com->command_with_arguments, data);
			process_redirect_envs(com->redirect_list, data);

            //int i = 0;
            //printf("\n--------------\n");
            //while ((com->command_with_arguments)[i] != NULL)
            //{
            //    printf("%s\n", (com->command_with_arguments[i]));
            //    i++;
            //}
            //printf("--------------\n");

			data->ar = com->command_with_arguments;
			if (data->redirect_list && !command->next)
				ft_check_redirects(data, command);
			else if (!data->redirect_list && command->next)
				ft_pipe(data);
			else if (data->redirect_list && command->next)
			{
				ft_check_redirects(data, command);
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
}
void loop(t_data *data)
{
	char *line;
	int flag;
	flag = 1;
	while (flag > 0)
	{
		g_code = 0;
		write(1, "minishell #> ", 13);
		flag = get_next_line(0, &line);
		process_command(data, line);
	}
}
int main(int ac, char **av, char **envp)
{
	t_data		data;

	make_env_list(&data, (const char **)envp);
	loop(&data);
	return (g_code);
}

//echo """"""""                 :            """" | cat -e