#include "parser/parse.h"
#include "functional/processing.h"

//TODO env not reload env_list
//TODO export if
//int main(int ac, char **av, char **envp)
//{
//	t_data data;
//	t_list *pipeline_list;
//	t_list *pipeline;
//	t_list *command_list;
//	t_list *command;
//	t_list *redirect;
//
//	t_command *com;
//	t_redirect *redir;
//	int i;
//
//	g_err = 0;
//	make_env_list(&data, (const char **)envp);
//	pipeline_list = parse_pipeline_list("ps | grep grep");
////						  "export>\">\"|grep>\"|\"<\">\" USER;"
////						  "ls > a > b -la;"
////						  "> a ls > b -la;"
////						  "ls > a ; chmod 111 a ; ls > a | cat -e;"
////						  "cat < a | cat -e");
//
//	pipeline = pipeline_list;
//	while (pipeline != NULL)
//	{
//		printf("\n======================== new pipeline ========================\n\n");
//		command_list = pipeline->content;
//		command = command_list;
//		while (command != NULL)
//		{
//			i = 0;
//			com = ((t_command *)(command->content));
//			data.redirect_list = com->redirect_list;
//			data.ar = com->command_with_arguments;
//			if (data.redirect_list && !command->next)
//				ft_check_redirects(&data);
//			else if (!data.redirect_list && command->next)
//			{
//				ft_pipe(&data);
//				com = ((t_command *)(command->content));
//				data.redirect_list = com->redirect_list;
//				data.ar = com->command_with_arguments;
//			}
//			else if (data.redirect_list && command->next)
//			{
//				ft_check_redirects(&data);
//				ft_pipe(&data);
//				com = ((t_command *)(command->content));
//				data.redirect_list = com->redirect_list;
//				data.ar = com->command_with_arguments;
//			}
//			else
//				check_command(&data);
//			command = command->next;
//		}
//		pipeline = pipeline->next;
//	}
//	free_pipeline_list(pipeline_list);
//	ft_write(1, ft_itoa(g_err));
//	write(1, "\n", 1);
//	return 0;
//}

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
//						  "export>\">\"|grep>\"|\"<\">\" USER;"
//						  "ls > a > b -la;"
//						  "> a ls > b -la;"
//						  "ls > a ; chmod 111 a ; ls > a | cat -e;"
//						  "cat < a | cat -e");

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
		pipeline = pipeline->next;
	}
	free_pipeline_list(pipeline_list);
//	ft_write(1, ft_itoa(g_err));
	write(1, "\n", 1);
}
void loop(char **envp)
{
	char *line;
	while (1)
	{
		write(1, "minishell #> ", 13);
		get_next_line(0, &line);
		process_command(line, envp);
		free(line);
	}
}
int main(int ac, char **av, char **envp)
{
	loop(envp);
	return 0;
}
