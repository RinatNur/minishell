#include "parser/parse.h"
#include <stdio.h>

int main()
{
	t_list *pipeline_list;
	t_list *pipeline;
	t_list *command_list;
	t_list *command;

	t_command *com;
	int i;

	pipeline_list = parse("echo ' asdfasd $PWD dffasdfa ' ");

	pipeline = pipeline_list;
	while (pipeline != NULL)
	{
		printf("--------------------------------\n");
		command_list = pipeline->content;
		command = command_list;
		while (command != NULL)
		{
			i = 0;
			com = ((t_command *)(command->content));
			while (com->command_with_arguments[i] != NULL)
			{
				printf("command: %s\n", com->command_with_arguments[i]);
				i++;
			}
			printf("redirects: %s\n\n", com->tmp);
			//printf("____%s", (char *)(command->content));
			command = command->next;
		}
		pipeline = pipeline->next;
	}
	return 0;
}
