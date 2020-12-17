/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 23:35:29 by jheat             #+#    #+#             */
/*   Updated: 2020/12/17 20:30:17 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*strdest;
	unsigned char	*strsrc;

	strdest = (unsigned char *)dest;
	strsrc = (unsigned char *)src;
	while (n--)
	{
		*strdest++ = *strsrc++;
		if (*(strdest - 1) == (unsigned char)c)
			return (strdest);
	}
	return (NULL);
}
