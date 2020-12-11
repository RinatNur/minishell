
#include "parse.h"

t_command *test(char **command_with_arguments, char *redirect_part)
{
	t_command *com;
	int i;

	i = 0;
	while (command_with_arguments[i] != NULL)
	{
		printf("%s\n", command_with_arguments[i]);
		i++;
	}


	com = malloc(sizeof(t_command));
	com->command_with_arguments = command_with_arguments;

	i = 0;
	while (com->command_with_arguments[i] != NULL)
	{
		printf("%s\n", com->command_with_arguments[i]);
		i++;
	}

	com->tmp = redirect_part;
	return (com);
}

t_command *parse_command(const char *command_str)
{
	char *command_part;
	char *redirect_part;
	int i;
	int len;

	len = 0;
	while (command_str[len] != '\0' && command_str[len] != '<' && command_str[len] != '>')
		len++;
	if (!(command_part = malloc(sizeof(char) * len + 1)))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		command_part[i] = command_str[i];
		i++;
	}
	command_part[i] = '\0';
	redirect_part = ft_strdup(command_str + len);


	char *mask;
	char **command_with_arguments;

	mask = get_mask(command_part);
	command_with_arguments = ft_split(command_part, ' ', mask);

	t_command *com;
	com = test(command_with_arguments, redirect_part);
	return (com);
}

