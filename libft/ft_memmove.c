/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 23:36:35 by jheat             #+#    #+#             */
/*   Updated: 2020/12/17 20:30:17 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*deststr;
	const unsigned char	*srcstr;

	deststr = dest;
	srcstr = src;
	if (srcstr >= deststr)
		ft_memcpy(deststr, srcstr, n);
	else
	{
		deststr += n;
		srcstr += n;
		while (n--)
			*--deststr = *--srcstr;
	}
	return (dest);
}
