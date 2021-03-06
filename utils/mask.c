/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:38:59 by wrudy             #+#    #+#             */
/*   Updated: 2021/01/14 17:39:05 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	mask_elem(unsigned char *flag, char symbol, char quote)
{
	if (symbol == quote)
	{
		*flag = ~(*flag);
		if (*flag == 1)
			return ('0');
	}
	if (*flag == 1)
		return ('0');
	else
		return (quote);
}

char	*get_mask(char *line)
{
	int				i;
	char			*result;
	unsigned char	flag;
	char			quote;

	if (!(result = malloc(sizeof(char) * u_strlen(line) + 1)))
		exit(EXIT_FAILURE);
	i = 0;
	flag = 1;
	quote = '\0';
	while (line[i] != '\0')
	{
		if (flag == 1 && (line[i] == '\'' || line[i] == '\"'))
		{
			quote = line[i];
			result[i] = '0';
			flag = ~flag;
			i++;
			continue ;
		}
		result[i] = mask_elem(&flag, line[i], quote);
		i++;
	}
	result[i] = 0;
	return (result);
}
