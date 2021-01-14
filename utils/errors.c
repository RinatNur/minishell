/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:42:37 by wrudy             #+#    #+#             */
/*   Updated: 2021/01/14 17:42:39 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "functional/processing.h"

void *exit_error1(char **str2)
{
	ft_error_print(MSHELL, "export", NULL, "not a valid identifier");
	free(str2);
	return NULL;
}

char **exit_error2(char **result, char *export_arg)
{
	int i;

	i = 0;
	while (result[0][i] != '\0')
	{
		if ((!ft_isalpha(export_arg[i])) && !ft_isdigit(export_arg[i]))
		{
			ft_error_print(MSHELL, "export", NULL, "not a valid identifier");
			free_2d_array(result);
			return (NULL);
		}
		i++;
	}
	return (result);
}
