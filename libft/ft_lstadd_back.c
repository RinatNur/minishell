/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <jheat@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/16 15:37:12 by jheat             #+#    #+#             */
/*   Updated: 2020/10/11 14:00:24 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list		*last;

	last = *lst;
	if (!last && lst)
		*lst = new;
	else if (lst && new)
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->next = NULL;
	}
}
