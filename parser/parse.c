/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:27:55 by wrudy             #+#    #+#             */
/*   Updated: 2021/01/14 17:27:59 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../functional/processing.h"

static t_list	*parse_pipeline(char *pipeline_line)
{
	t_list		*command_list;
	char		*mask;
	char		**command_array;
	int			i;

	command_list = NULL;
	mask = get_mask(pipeline_line);
	command_array = u_split(pipeline_line, '|', mask);
	i = 0;
	while (command_array[i] != NULL)
	{
		addback(&command_list,
				lstnew(parse_command(command_array[i])));
		i++;
	}
	free(mask);
	free_2d_array(command_array);
	return (command_list);
}

static void		fill_pipeline_list(t_list **pipeln_list, char **pipeline_lines)
{
	int		i;
	t_list	*pipeline;
	t_list	*command_list;

	i = 0;
	while (pipeline_lines[i] != NULL)
	{
		command_list = parse_pipeline(pipeline_lines[i]);
		pipeline = lstnew(command_list);
		addback(pipeln_list, pipeline);
		i++;
	}
}

t_list			*parse_pipeline_list(char *command_line)
{
	t_list	*pipeline_list;
	char	**pipeline_lines;
	char	*mask;

	mask = get_mask(command_line);
	pipeline_lines = u_split(command_line, ';', mask);
	if (!validate(command_line, mask, pipeline_lines))
	{
		free_2d_array(pipeline_lines);
		free(mask);
		return (NULL);
	}
	pipeline_list = NULL;
	fill_pipeline_list(&pipeline_list, pipeline_lines);
	free_2d_array(pipeline_lines);
	free(mask);
	return (pipeline_list);
}

void			free_pipeline_list(t_list *pipeline_list)
{
	t_list *pipeline;
	t_list *command_list;

	pipeline = pipeline_list;
	while (pipeline != NULL)
	{
		command_list = pipeline->content;
		ft_lstclear(&command_list, (void (*)(void *))command_destructor);
		pipeline = pipeline->next;
	}
	empty_lst_clear(&pipeline_list);
}
