/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 15:37:12 by jheat             #+#    #+#            /*   Updated: 2020/12/17 20:30:17 by wrudy            ###   ########.fr       */
 */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list        *last;

	last = *lst;
	if (!last)
		*lst = new;
	else if (*lst && new)
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->next = NULL;
	}
}
