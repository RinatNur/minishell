/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 20:36:54 by jheat             #+#    #+#             */
/*   Updated: 2021/01/13 20:37:09 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

t_env		*sort_env_list(t_sort_env *data)
{
	data->out = NULL;
	while (data->ph)
	{
		data->q = data->ph;
		data->ph = data->ph->next;
		data->p = data->out;
		data->pr = NULL;
		while (data->p && (ft_strncmp(PKEY, QKEY, (ft_strlen(QKEY) + 1))) < 0)
		{
			data->pr = data->p;
			data->p = data->p->next;
		}
		if (data->pr == NULL)
		{
			data->q->next = data->out;
			data->out = data->q;
		}
		else
		{
			data->q->next = data->p;
			data->pr->next = data->q;
		}
	}
	data->ph = data->out;
	return (data->ph);
}

t_env		*copy_list(t_env *list)
{
	t_env		*tmp;

	tmp = NULL;
	while (list)
	{
		if (list->value == NULL)
			ft_lstadd_back_env(&tmp, ft_lstnew_env(ft_strdup(list->key), NULL));
		else
			ft_lstadd_back_env(&tmp, ft_lstnew_env(ft_strdup(list->key),
								ft_strdup(list->value)));
		list = list->next;
	}
	return (tmp);
}

int			cut_list_if_it_not_last(t_env **list)
{
	t_env *tmp;

	if ((*list)->prev == NULL)
	{
		tmp = *list;
		*list = (*list)->next;
		free_env_content(tmp);
		free(tmp);
		(*list)->prev = NULL;
		return (0);
	}
	else if ((*list)->next != NULL)
	{
		tmp = (*list)->prev;
		*list = (*list)->next;
		free_env_content((*list)->prev);
		free((*list)->prev);
		(*list)->prev = tmp;
		tmp->next = *list;
		return (1);
	}
}

t_env		*cut_list(t_data *data, char *ar)
{
	t_env		*list;
	t_env		*tmp;
	size_t		len;

	list = data->env_list;
	len = ft_strlen(ar) + 1;
	while (list->next)
	{
		if (!ft_strncmp(ar, list->key, len))
			if (cut_list_if_it_not_last(&list))
				break ;
		list = list->next;
	}
	if (!ft_strncmp(ar, list->key, len))
		if (list->next == NULL)
		{
			tmp = list;
			list = list->prev;
			free_env_content(tmp);
			free(tmp);
			list->next = NULL;
		}
	while (list->prev)
		list = list->prev;
	return ((data->env_list = list));
}
