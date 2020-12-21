/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 16:11:01 by wrudy             #+#    #+#             */
/*   Updated: 2020/05/29 16:14:53 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	size_t i;

	i = 0;
	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}

char		*u_strdup(const char *s)
{
	char *duplicate;

	if ((duplicate = malloc((u_strlen(s) + 1) * sizeof(char))) == NULL)
		exit(EXIT_FAILURE);
	ft_strcpy(duplicate, s);
	return (duplicate);
}
