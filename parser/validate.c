/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:31:45 by wrudy             #+#    #+#             */
/*   Updated: 2021/01/14 17:31:57 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functional/processing.h"
#include "parse.h"

int		is_empty(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int		find_unexpected_token1(char *str)
{
	int		i;
	char	*mask;

	i = 0;
	mask = get_mask(str);
	while (str[i] != '\0')
	{
		if ((str[i] == '|' && str[i + 1] == '|') &&
			(mask[i] == '0' && mask[i + 1] == '0'))
		{
			ft_error("-minishell: syntax error near unexpected token: |", 2);
			free(mask);
			return (1);
		}
		i++;
	}
	free(mask);
	return (0);
}

int		find_unexpected_token2(char *str)
{
	int		i;
	char	*mask;

	i = 0;
	mask = get_mask(str);
	while (str[i] != '\0')
	{
		if ((str[i] == ';' && str[i + 1] == ';') &&
			(mask[i] == '0' && mask[i + 1] == '0'))
		{
			ft_error("-minishell: syntax error near unexpected token: ;", 2);
			free(mask);
			return (1);
		}
		i++;
	}
	free(mask);
	return (0);
}

int		find_unexpected_token3(char **pipeline_lines)
{
	int i;

	i = 0;
	while (pipeline_lines[i] != NULL)
	{
		if (is_empty(pipeline_lines[i]) && pipeline_lines[i + 1] != NULL)
		{
			ft_error("-minishell: syntax error near unexpected token: ;", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int		validate(char *command_line, char *mask, char **pipeline_lines)
{
	char **arr;
	char *clear_command_line;

	arr = u_split(command_line, ' ', mask);
	clear_command_line = arr_strjoin(arr);
	if (find_unexpected_token1(clear_command_line)
		|| find_unexpected_token2(clear_command_line)
		|| find_unexpected_token3(pipeline_lines))
	{
		free_2d_array(arr);
		free(clear_command_line);
		return (0);
	}
	free_2d_array(arr);
	free(clear_command_line);
	return (1);
}
