#include "parser/parse.h"
#include "functional/processing.h"

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
			i = 0;
			com = ((t_command *)(command->content));
			data.redirect_list = com->redirect_list;
			data.ar = com->command_with_arguments;
			if (data.redirect_list && !command->next)
				ft_check_redirects(&data);
			else if (!data.redirect_list && command->next)
			{
				ft_pipe(&data);
				com = ((t_command *)(command->content));
				data.redirect_list = com->redirect_list;
				data.ar = com->command_with_arguments;
			}
			else if (data.redirect_list && command->next)
			{
				ft_check_redirects(&data);
				ft_pipe(&data);
				com = ((t_command *)(command->content));
				data.redirect_list = com->redirect_list;
				data.ar = com->command_with_arguments;
			}
			else
				check_command(&data);
			command = command->next;
		}
		dup2(1, 0);
		pipeline = pipeline->next;
	}
	free_pipeline_list(pipeline_list);
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
		free(line);
	}
}
int main(int ac, char **av, char **envp)
{
	loop(envp);
	return 0;
}
