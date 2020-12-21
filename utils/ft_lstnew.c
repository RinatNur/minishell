/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:02:43 by wrudy             #+#    #+#             */
/*   Updated: 2020/05/29 16:03:14 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_elem;

	if (!(new_elem = (t_list*)malloc(sizeof(*new_elem))))
		return (NULL);
	new_elem->content = content;
	new_elem->next = NULL;
	return (new_elem);
}
