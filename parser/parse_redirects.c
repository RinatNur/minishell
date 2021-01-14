
#include "parse.h"
#include "libft.h"

int error(t_command *cmd, const char *command, char **filename, int i)
{
	char token[2] = {0};

	*filename = ft_strdup("");
	if (command[i] != '\0')
	{
		token[0] = command[i];
		cmd->parse_error = ft_strjoin("Syntax error near unexpected token (after redirect): ", token);
	}
	else
		cmd->parse_error = ft_strjoin("Syntax error near unexpected token (after redirect): ", "'end of command'");
	return (0);
}

static int get_filename(const char *command, const char *mask, char **filename, t_command *cmd)
{
	int i;
	int len;
	char *fname;
	int result;

	i = 1;
	while (command[i] == ' ')
		i++;
	if ((find_char("><|;()", command[i]) != -1) || command[i] == '\0')
		return (error(cmd, command, filename, i));
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

static int set_offset(int offset, int *i, t_redirect *redirect, t_rtype type)
{
	redirect->redirect_type = type;
	(*i) = (*i) + offset;
	return (offset);
}

static t_redirect *get_redirect(int *i, char *command, char *quote_mask, t_command *cmd)
{
	t_redirect *redirect;

	redirect = redirect_constructor(0, NULL);
	if (command[(*i)] == '>')
	{
		if (command[*(i) + 1] == '>')
		{
			(*i)++;
			if (!set_offset(get_filename
			(command + (*i), quote_mask + (*i), &redirect->filename, cmd),
			i, redirect, into_file_with_rewrite))
				return (redirect);
		}
		else
			if (!set_offset(get_filename
			(command + (*i), quote_mask + (*i), &redirect->filename, cmd),
			i, redirect, into_file))
				return (redirect);
	}
	if (command[(*i)] == '<')
		if (!set_offset(get_filename
		(command + (*i), quote_mask + (*i), &redirect->filename, cmd),
		i, redirect, from_file))
			return (redirect);
	return (redirect);
}

t_list		*parse_redirects(char **command, t_command *cmd)
{
	int		i;
	char	*quote_mask;
	t_list	*result;
	char	*clear_command;

	quote_mask = get_mask(*command);
	i = 0;
	result = NULL;
	clear_command = empty_str(' ', u_strlen(*command));
	i = 0;
	while ((*command)[i] != '\0')
	{
		if (quote_mask[i] == '0' && ((*command)[i] == '>' || (*command)[i] == '<'))
			ft_lstadd_back(&result, ft_lstnew(get_redirect(&i, *command, quote_mask, cmd)));
		else
			clear_command[i] = (*command)[i];
		if (cmd->parse_error != NULL)
			break;
		i++;
	}
	free(*command);
	free(quote_mask);
	*command = clear_command;
	return (result);
}
