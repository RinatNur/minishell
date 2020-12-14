
#include "parse.h"

t_command			*command_constructor(char **command_with_arguments, t_list *redirect_list, t_list *option_list)
{
	t_command *result;

	if (!(result = malloc(sizeof(t_command))))
		exit(EXIT_FAILURE);
	result->command_with_arguments = command_with_arguments;
	result->redirect_list = redirect_list;
	result->option_list = option_list;
	return (result);
}

void 				command_destructor(t_command *command)
{
	int i;

	i = 0;
	while (command->command_with_arguments[i] != NULL)
	{
		free(command->command_with_arguments[i]);
		i++;
	}
	free(command->command_with_arguments);
	ft_lstclear(&(command->redirect_list), (void (*)(void *))redirect_destructor);
	ft_lstclear(&(command->option_list), free);
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
