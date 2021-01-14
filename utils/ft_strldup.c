/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:38:39 by wrudy             #+#    #+#             */
/*   Updated: 2021/01/14 17:38:42 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "utils.h"

static size_t	ft_strlcpy(char *dest, const char *src, size_t l)
{
	size_t i;

	if (l == 0)
		return (u_strlen(src));
	i = 0;
	while (*(src + i) != '\0' && i < l)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (u_strlen(src));
}

char			*u_strldup(const char *s, size_t l)
{
	char *duplicate;

	if ((duplicate = malloc((l + 1) * sizeof(char))) == NULL)
		exit(EXIT_FAILURE);
	ft_strlcpy(duplicate, s, l);
	return (duplicate);
}
