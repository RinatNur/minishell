#include "parser/parse.h"
#include <stdio.h>


int main()
{
	t_list *pipeline_list;
	t_list *pipeline;
	t_list *command_list;
	t_list *command;

	pipeline_list = parse("dsa|jidsbg|dsahjvh;fsa||djhf|uhd|uos;;fdh|fd;df|sjdsij;s|jifd");

	pipeline = pipeline_list;
	while (pipeline != NULL)
	{
		command_list = pipeline->content;
		command = command_list;
		while (command != NULL)
		{
			printf("____%s", (char *)(command->content));
			command = command->next;
		}
		printf("\n");
		pipeline = pipeline->next;
	}
	return 0;
}
