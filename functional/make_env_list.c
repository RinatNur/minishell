/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 20:46:44 by jheat             #+#    #+#             */
/*   Updated: 2021/01/13 20:46:45 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

void		make_env_list(t_data *data, const char **env)
{
	t_env		*list;
	char		**env_split;
	int			i;

	i = 0;
	env_split = NULL;
	list = NULL;
	while (env[i])
	{
		env_split = ft_split(env[i], '=');
		if (!ft_strncmp("OLDPWD", env_split[0], 7))
		{
			if (env_split[1] != NULL)
				free(env_split[1]);
			env_split[1] = NULL;
		}
		if (env_split[1] == NULL)
			LSTADD(&list, LSTNEW(DUP(env_split[0]), NULL));
		else
			LSTADD(&list, LSTNEW(DUP(env_split[0]), DUP(env_split[1])));
		free_arr(env_split);
		i++;
	}
	data->env_list = list;
}
