/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 17:14:02 by jheat             #+#    #+#             */
/*   Updated: 2021/01/13 17:14:04 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

void			free_env_content(t_env *list)
{
	free(list->key);
	if (list->value != NULL)
		free(list->value);
}

void			free_env_list(t_env *list)
{
	t_env *tmp;

	while (list)
	{
		free_env_content(list);
		tmp = list;
		list = list->next;
		free(tmp);
	}
	free(list);
}
