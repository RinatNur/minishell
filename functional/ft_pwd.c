/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:30:43 by jheat             #+#    #+#             */
/*   Updated: 2021/01/13 18:30:44 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

void		ft_pwd(void)
{
	char		*dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	if (!dir)
	{
		g_code = errno;
		ft_error_print(MSHELL, "pwd", NULL, strerror(errno));
	}
	ft_write(1, dir);
	write(1, "\n", 1);
	free(dir);
}
