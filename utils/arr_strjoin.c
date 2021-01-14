/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_strjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:33:11 by wrudy             #+#    #+#             */
/*   Updated: 2021/01/14 17:33:14 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*arr_strjoin(char **line)
{
	int		i;
	char	*result;
	char	*tmp;

	i = 1;
	if (line[0] == NULL)
		return (u_strdup(""));
	result = u_strdup(line[0]);
	while (line[i] != NULL)
	{
		tmp = u_strjoin(result, line[i]);
		free(result);
		result = tmp;
		i++;
	}
	return (result);
}
