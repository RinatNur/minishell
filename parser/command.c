
#include "parse.h"

t_command			*command_constructor(char **command_with_arguments, t_list *redirect_list)
{
	t_command *result;

	if (!(result = malloc(sizeof(t_command))))
		exit(EXIT_FAILURE);
	result->command_with_arguments = command_with_arguments;
	result->redirect_list = redirect_list;
	result->parse_error = NULL;
	return (result);
}

void 				command_destructor(t_command *command)
{
	free_2d_array(command->command_with_arguments);
	if (command->parse_error != NULL)
	    free(command->parse_error);
	ft_lstclear(&(command->redirect_list), (void (*)(void *))redirect_destructor);
	free(command);
}

t_redirect			*redirect_constructor(t_rtype redirect_type, char *filename)
{
	t_redirect *result;

	if (!(result = malloc(sizeof(t_redirect))))
		exit(EXIT_FAILURE);
	result->filename = filename;
	result->redirect_type = redirect_type;
	return (result);
}

void 				redirect_destructor(t_redirect *redirect)
{
	free(redirect->filename);
	free(redirect);
}
