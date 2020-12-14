#include "parser/parse.h"
#include <stdio.h>

static int get_filename(const char *command, const char *mask, char **filename)
{
	int i;
	int len;
	char *fname;
	int result;

	i = 1;
	while (command[i] == ' ')
		i++;
	len = 0;
	while ((command[i + len] != ' ' || mask[i + len] != '0') && command[i + len] != '\0'
			&& command[i + len] != '>' && command[i + len] != '<')
		len++;
	if (!(fname = malloc(sizeof(char) * len + 1)))
		exit(EXIT_FAILURE);
	result = i + len;

	fname[len] = '\0';

	while (len--)
		fname[len] = command[i + len];
	*filename = fname;
	return (result - 1);
}

static t_list		*parse_redirects(char **command)
{
	int i;
	char *quote_mask;
	t_redirect *redirect;
	t_list	*result;
	char *clear_command;
	size_t command_len;


	quote_mask = get_mask(*command);
	i = 0;
	result = NULL;
	command_len = ft_strlen(*command);
	if (!(clear_command = malloc(sizeof(char) * command_len + 1)))
		exit(EXIT_FAILURE);
	while (i < command_len)
	{
		clear_command[i] = 'r';
		i++;
	}
	clear_command[i] = 0;
	i = 0;
	while ((*command)[i] != '\0')
	{
		if (quote_mask[i] == '0' && ((*command)[i] == '>' || (*command)[i] == '<'))
		{
			redirect = redirect_constructor(0, NULL);
			if ((*command)[i] == '>')
			{
				if ((*command)[i + 1] == '>')
				{
					i++;
					redirect->redirect_type = into_file_with_rewrite;
					i = i + get_filename((*command) + i, quote_mask + i, &redirect->filename);
				}
				else
				{
					redirect->redirect_type = into_file;
					i = i + get_filename((*command) + i, quote_mask + i, &redirect->filename);
				}
			}
			if ((*command)[i] == '<')
			{
				redirect->redirect_type = from_file;
				i = i + get_filename((*command) + i, quote_mask + i, &redirect->filename);
			}
			ft_lstadd_back(&result, ft_lstnew(redirect));
		}
		else
			clear_command[i] = (*command)[i];
		i++;
	}
	//free(*command);
	*command = clear_command;
	return (result);
}









int main()
{
	//char *command = "";
	//t_list *test;
	//t_redirect *redirect;
//
	//test = parse_redirects(&command);
	//while (test != NULL)
	//{
	//	redirect = (t_redirect *)(test->content);
	//	if (redirect->redirect_type == 0)
	//		printf("type:  %s\n", "<");
	//	else if (redirect->redirect_type == 1)
	//		printf("type:  %s\n", ">");
	//	else
	//		printf("type:  %s\n", ">>");
	//	printf("name: %s\n", redirect->filename);
	//	test = test->next;
	//}
	//printf("\n%s", command);
	//return (0);

	t_list *pipeline_list;
	t_list *pipeline;
	t_list *command_list;
	t_list *command;
	t_list *redirect;

	t_command *com;
	t_redirect *redir;
	int i;

	pipeline_list = parse("export>a|grep>b<a USER Dfasdfasdfasdfasdfasasd ; echo $?;"
						  "export>\">\"|grep>\"|\"<\">\" USER;"
						  "ls > a > b -la;"
						  "> a ls > b -la;"
						  "ls > a ; chmod 111 a ; ls > a | cat -e;"
						  "cat < a | cat -e");

	pipeline = pipeline_list;
	while (pipeline != NULL)
	{
		printf("\n======================== new command ========================\n\n");
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
					if (redir->redirect_type == 0)
						printf("redirect type:  %s  ", "<");
					else if (redir->redirect_type == 1)
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
	return 0;
}
