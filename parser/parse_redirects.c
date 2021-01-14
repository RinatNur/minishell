/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:28:51 by wrudy             #+#    #+#             */
/*   Updated: 2021/01/14 17:28:54 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "libft.h"

static int			error(
		t_command *cmd, const char *command, char **filename, int i)
{
	char token[2];

	token[0] = 0;
	token[1] = 0;
	*filename = ft_strdup("");
	if (command[i] != '\0')
	{
		token[0] = command[i];
		cmd->parse_error = ft_strjoin(
		"Syntax error near unexpected token (redirect): ", token);
	}
	else
		cmd->parse_error = ft_strjoin(
		"Syntax error near unexpected token (redirect): ", "'end of command'");
	return (0);
}

static int			get_filename(
		const char *command, const char *mask, char **filename, t_command *cmd)
{
	int		i;
	int		len;
	char	*fname;
	int		result;

	i = 1;
	while (command[i] == ' ')
		i++;
	if ((find_char("><|;()", command[i]) != -1) || command[i] == '\0')
		return (error(cmd, command, filename, i));
	len = 0;
	while ((command[i + len] != ' ' || mask[i + len] != '0')
	&& command[i + len] != '\0'
	&& !(command[i + len] == '>' && mask[i + len] == '0')
	&& !(command[i + len] == '<' && mask[i + len] == '0'))
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

static int			set_offset(
		int offset, int *i, t_redirect *redirect, t_rtype type)
{
	redirect->redirect_type = type;
	(*i) = (*i) + offset;
	return (offset);
}

static t_redirect	*get_redirect(
		int *i, char *command, char *quote_mask, t_command *cmd)
{
	t_redirect *redirect;

	redirect = redirect_constructor(0, NULL);
	if (command[(*i)] == '>')
	{
		if (command[*(i) + 1] == '>')
		{
			(*i)++;
			if (!set_offset(get_filename(
			command + (*i), quote_mask + (*i), &redirect->filename, cmd),
					i, redirect, into_file_with_rewrite))
				return (redirect);
		}
		else if (!set_offset(get_filename(
			command + (*i), quote_mask + (*i), &redirect->filename, cmd),
					i, redirect, into_file))
			return (redirect);
	}
	if (command[(*i)] == '<')
		if (!set_offset(get_filename(
		command + (*i), quote_mask + (*i), &redirect->filename, cmd),
		i, redirect, from_file))
			return (redirect);
	return (redirect);
}

t_list				*parse_redirects(char **com, t_command *cmd)
{
	int		i;
	char	*quote_mask;
	t_list	*result;
	char	*clear_command;

	quote_mask = get_mask(*com);
	i = 0;
	result = NULL;
	clear_command = empty_str(' ', u_strlen(*com));
	i = 0;
	while ((*com)[i] != '\0')
	{
		if (quote_mask[i] == '0' && ((*com)[i] == '>' || (*com)[i] == '<'))
			addback(&result, lstnew(get_redirect(&i, *com, quote_mask, cmd)));
		else
			clear_command[i] = (*com)[i];
		if (cmd->parse_error != NULL)
			break ;
		i++;
	}
	free(*com);
	free(quote_mask);
	*com = clear_command;
	return (result);
}
