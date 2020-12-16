#include "parser/parse.h"
#include <stdio.h>


int main()
{
	//TODO Заменять где нужно переменные окружения на их значения
	//TODO Убирать из аргументов команд и редиректов кавычки
	//TODO Привести к норме
	t_list *pipeline_list;
	t_list *pipeline;
	t_list *command_list;
	t_list *command;
	t_list *redirect;

	t_command *com;
	t_redirect *redir;
	int i;

	pipeline_list = parse_pipeline_list("export>a|grep>b<a USER Dfasdfasdfasdfasdfasasd ; echo $?;"
										"export>\">\"|grep>\"|\"<\">\" USER;"
										"ls > a > b -la;"
										"> a ls > b -la;"
										"ls > a ; chmod 111 a ; ls > a | cat -e;"
										"cat < a | cat -e");

	pipeline = pipeline_list;
	while (pipeline != NULL)
	{
		printf("\n======================== new pipeline ========================\n\n");
		command_list = pipeline->content;
		command = command_list;
		while (command != NULL)
		{
			i = 0;
			com = ((t_command *)(command->content));
			while (com->command_with_arguments[i] != NULL)
			{
				if (i == 0)
					printf("command: %s\n", com->command_with_arguments[i]);
				else
					printf("argument: %s\n", com->command_with_arguments[i]);
				i++;
			}
			redirect = com->redirect_list;
			while (redirect != NULL)
			{
				redir = (t_redirect *)(redirect->content);
					if (redir->redirect_type == from_file)
						printf("redirect type:  %s  ", "<");
					else if (redir->redirect_type == into_file)
						printf("redirect type:  %s  ", ">");
					else
						printf("redirect type:  %s  ", ">>");
					printf("filename: %s\n", redir->filename);
				redirect = redirect->next;
			}
			if (command->next != NULL)
				printf("\n-------- pipe -------\n\n");
			command = command->next;
		}
		pipeline = pipeline->next;
	}
	free_pipeline_list(pipeline_list);
	return 0;
}
