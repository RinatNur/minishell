/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_pars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 16:11:01 by wrudy             #+#    #+#           /*   Updated: 2020/12/17 20:30:17 by wrudy            ###   ########.fr       */
  */
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

char		*ft_strdup_pars(const char *s)
{
	char *duplicate;

	if ((duplicate = malloc((ft_strlen_pars(s) + 1) * sizeof(char))) == NULL)
		exit(EXIT_FAILURE);
	ft_strcpy(duplicate, s);
	return (duplicate);
}
