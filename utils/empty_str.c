/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:33:39 by wrudy             #+#    #+#             */
/*   Updated: 2021/01/14 17:33:41 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*empty_str(char c, int len)
{
	char	*result;
	int		i;

	if (!(result = malloc(sizeof(char) * len + 1)))
		exit(EXIT_FAILURE);
	i = 0;
	while (i < len)
	{
		result[i] = c;
		i++;
	}
	result[i] = 0;
	return (result);
}
