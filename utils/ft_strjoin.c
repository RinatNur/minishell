/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:30:06 by wrudy             #+#    #+#             */
/*   Updated: 2021/01/14 19:30:10 by wrudy            ###   ########.fr       */
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

char		*u_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	len_s1;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = u_strlen(s1);
	if ((res = malloc((len_s1 + u_strlen(s2) + 1) * sizeof(char))) == NULL)
		exit(EXIT_FAILURE);
	ft_strcpy(res, s1);
	ft_strcpy(res + len_s1, s2);
	return (res);
}
