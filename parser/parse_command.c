
#include "parse.h"

static t_command	*parse_clear_command(char *clear_command, t_list *redirects, t_command *cmd)
{
	char **command_with_args;
	char *mask;

	mask = get_mask(clear_command);
	command_with_args = u_split(clear_command, ' ', mask);
	free(mask);
	cmd->command_with_arguments = command_with_args;
	cmd->redirect_list = redirects;
	return (cmd);
}

t_command			*parse_command(const char *command_str)
{
	t_command	*command;
	t_list		*redirect_list;
	char 		*clear_command_str;

	clear_command_str = u_strdup(command_str);

	command = command_constructor(NULL, NULL);
	redirect_list = parse_redirects(&clear_command_str, command);
	if (command->parse_error != NULL)
	{
		command->redirect_list = redirect_list;
		free(clear_command_str);
		return (command);
	}
	parse_clear_command(clear_command_str, redirect_list, command);

	free(clear_command_str);
	return (command);
}

