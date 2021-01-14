/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:27:04 by wrudy             #+#    #+#             */
/*   Updated: 2021/01/14 17:27:13 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_command	*command_constructor(char **cmd_with_arguments, t_list *redir_lst)
{
	t_command *result;

	if (!(result = malloc(sizeof(t_command))))
		exit(EXIT_FAILURE);
	result->command_with_arguments = cmd_with_arguments;
	result->redirect_list = redir_lst;
	result->parse_error = NULL;
	return (result);
}

void		command_destructor(t_command *command)
{
	free_2d_array(command->command_with_arguments);
	if (command->parse_error != NULL)
		free(command->parse_error);
	ft_lstclear(&(command->redirect_list),
			(void (*)(void *))redirect_destructor);
	free(command);
}

t_redirect	*redirect_constructor(t_rtype redirect_type, char *filename)
{
	t_redirect *result;

	if (!(result = malloc(sizeof(t_redirect))))
		exit(EXIT_FAILURE);
	result->filename = filename;
	result->redirect_type = redirect_type;
	return (result);
}

void		redirect_destructor(t_redirect *redirect)
{
	free(redirect->filename);
	free(redirect);
}
