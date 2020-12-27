
#include "parse.h"

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
		   && !(command[i + len] == '>' && mask[i + len] == '0') && !(command[i + len] == '<' && mask[i + len] == '0'))
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

static t_redirect *get_redirect(int *i, char *command, char *quote_mask)
{
	t_redirect *redirect;

	redirect = redirect_constructor(0, NULL);
	if (command[*i] == '>')
	{
		if (command[*(i) + 1] == '>')
		{
			(*i)++;
			redirect->redirect_type = into_file_with_rewrite;
			(*i) = (*i) + get_filename(command + (*i), quote_mask + (*i), &redirect->filename);
		}
		else
		{
			redirect->redirect_type = into_file;
			(*i) = (*i) + get_filename(command + (*i), quote_mask + (*i), &redirect->filename);
		}
	}
	if (command[(*i)] == '<')
	{
		redirect->redirect_type = from_file;
		(*i) = (*i) + get_filename(command + (*i), quote_mask + (*i), &redirect->filename);
	}
	return (redirect);
}

static t_list		*parse_redirects(char **command)
{
	int i;
	char *quote_mask;
	t_list	*result;
	char *clear_command;

	quote_mask = get_mask(*command);
	i = 0;
	result = NULL;
	clear_command = empty_str(' ', u_strlen(*command));
	i = 0;
	while ((*command)[i] != '\0')
	{
		if (quote_mask[i] == '0' && ((*command)[i] == '>' || (*command)[i] == '<'))
			ft_lstadd_back(&result, ft_lstnew(get_redirect(&i, *command, quote_mask)));
		else
			clear_command[i] = (*command)[i];
		i++;
	}
	free(*command);
	free(quote_mask);
	*command = clear_command;
	return (result);
}

static t_command	*parse_clear_command(char *clear_command, t_list *redirects)
{
	t_command *result;
	char **command_with_args;
	char *mask;

	mask = get_mask(clear_command);
	command_with_args = u_split(clear_command, ' ', mask);
	free(mask);
	result = command_constructor(command_with_args, redirects);
	return (result);
}

t_command			*parse_command(const char *command_str)
{
	t_command	*command;
	t_list		*redirect_list;
	char 		*clear_command_str;

	clear_command_str = u_strdup(command_str);
	redirect_list = parse_redirects(&clear_command_str);
	command = parse_clear_command(clear_command_str, redirect_list);
	free(clear_command_str);
	return (command);
}

