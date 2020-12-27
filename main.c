#include "parser/parse.h"
#include <stdio.h>
#include <unistd.h>
#include "gnl/get_next_line.h"

void process_command(char *command_line)
{
	//TODO Заменять где нужно переменные окружения на их значения
	//TODO Убирать из аргументов команд и редиректов кавычки
	//TODO Привести к норме
	t_list *pipeline_list;
	t_list *pipeline;
	t_list *command_list;
	t_list *command;
	t_list *redirect_list;

	char **command_with_arguments;
	t_redirect *redirect;

	int i;

	pipeline_list = parse_pipeline_list(command_line);

	pipeline = pipeline_list;
	while (pipeline != NULL)
	{
		printf("\n======================== new pipeline ========================\n\n");

		command_list = pipeline->content;
		command = command_list;
		while (command != NULL)
		{
			command_with_arguments = ((t_command *)(command->content))->command_with_arguments;
			redirect_list = ((t_command *)(command->content))->redirect_list;

			i = 0;
			while (command_with_arguments[i] != NULL)
			{
				if (i == 0)
					printf("command: %s\n", command_with_arguments[i]);
				else
					printf("argument: %s\n", command_with_arguments[i]);
				i++;
			}

			while (redirect_list != NULL)
			{
				redirect = (t_redirect *)(redirect_list->content);
				if (redirect->redirect_type == from_file)
					printf("redirect_list type:  %s  ", "<");
				else if (redirect->redirect_type == into_file)
					printf("redirect_list type:  %s  ", ">");
				else
					printf("redirect_list type:  %s  ", ">>");
				printf("filename: %s\n", redirect->filename);
				redirect_list = redirect_list->next;
			}

			if (command->next != NULL)
				printf("\n-------- pipe -------\n\n");
			command = command->next;
		}
		pipeline = pipeline->next;
	}
	free_pipeline_list(pipeline_list);
}

void loop()
{
	char *line;
	int error;
	int i;
	char **test;

	error = 1;
	while (error > 0)
	{
		write(1, "minishell #> ", 13);
		error = get_next_line(0, &line);
		//process_command(line);
		i = 0;
		test = process_export_arg(line);
		while (test[i] != NULL)
		{
			printf("%s\n", test[i]);
			i++;
		}
		free(line);
	}
}

int main()
{
	loop();
	return 0;
}
