/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 19:16:48 by jheat             #+#    #+#             */
/*   Updated: 2021/01/13 19:16:50 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

void		ft_unset(t_data *data)
{
	size_t		len;
	t_env		*list;
	int			i;

	i = 1;
	list = data->env_list;
	while (data->ar[i])
	{
		len = ft_strlen(data->ar[i]) + 1;
		while (list)
		{
			if (!(ft_strncmp(data->ar[i], list->key, len)))
			{
				cut_list(data, data->ar[i]);
				list = data->env_list;
				break ;
			}
			list = list->next;
		}
		i++;
	}
}
