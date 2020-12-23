#include "parser/parse.h"
#include "functional/processing.h"

//TODO grep make < a | cat -e
//TODO ls >a | cat -e
//TODO ls full space in the enf of file
//TODO free_2d_array in libft not used anyway
//TODO Roma realize .. -> one dir back
//TODO Roma env list clears every loop

void		ft_pipe_eof(void)
{
	int mas[2];

	pipe(mas);
	write(mas[1], "", 0);
	dup2(mas[0], 0);
//	dup2(mas[1], 1);
//	close(mas[0]);
	close(mas[1]);
}

void		init_data(t_data *data, t_list **command, t_command **com)
{
	*com = ((t_command *)((*command)->content));
	data->redirect_list = (*com)->redirect_list;

//	process_envs(((*com)->command_with_arguments), data);

	data->ar = (*com)->command_with_arguments;
}

static void process_command(char *command_line, char **envp)
{
	t_data data;
	t_list *pipeline_list;
	t_list *pipeline;
	t_list *command_list;
	t_list *command;
	t_list *redirect;

	t_command *com;
	t_redirect *redir;
	int i;

	g_err = 0;
	data.redir_flag = 0;
	data.fd_start[0] = dup(0);
	data.fd_start[1] = dup(1);
	make_env_list(&data, (const char **)envp);
	pipeline_list = parse_pipeline_list(command_line);
	pipeline = pipeline_list;
	while (pipeline != NULL)
	{
//		printf("\n======================== new pipeline ========================\n\n");
		command_list = pipeline->content;
		command = command_list;
		while (command != NULL)
		{
//			init_data(&data, &command, &com);
			com = ((t_command *)(command->content));
			data.redirect_list = com->redirect_list;

			process_envs((com->command_with_arguments), &data);

			data.ar = com->command_with_arguments;
			if (data.redirect_list && !command->next)
				ft_check_redirects(&data);
			else if (!data.redirect_list && command->next)
				ft_pipe(&data);
			else if (data.redirect_list && command->next)
			{
				ft_check_redirects(&data);
				if (data.redir_pipe_flag)
				{
					command = command->next;
					init_data(&data, &command, &com);
					check_command(&data);//TODO remove after tests
				}
				else
					ft_pipe(&data);
			}
			else
			{
				if (data.redir_flag)
					ft_pipe_eof();
				check_command(&data);
			}
			command = command->next;
		}
		dup2(1, 0);//to return fd 0 back;
		pipeline = pipeline->next;
	}
//	free_pipeline_list(pipeline_list);
}
void loop(char **envp)
{
	char *line;
	int flag;
	flag = 1;
	while (flag > 0)
	{
		write(1, "minishell #> ", 13);
		flag = get_next_line(0, &line);
		process_command(line, envp);
//		free(line);
	}
}
int main(int ac, char **av, char **envp)
{
	loop(envp);
	return 0;
}
