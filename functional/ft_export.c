/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:57:50 by jheat             #+#    #+#             */
/*   Updated: 2021/01/13 16:57:55 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"
#include "./utils/utils.h"

static void		print_env_list(t_data *data, t_env *sort_l)
{
	t_sort_env		sort_env;

	sort_env.ph = copy_list(data->env_list);
	sort_l = sort_env_list(&sort_env);
	while (sort_l)
	{
		ft_write(1, "declare -x ");
		ft_write(1, sort_l->key);
		if (sort_l->value)
		{
			ft_write(1, "=\"");
			ft_write(1, sort_l->value);
			ft_write(1, "\"");
		}
		sort_l = sort_l->next;
		ft_write(1, "\n");
	}
	free_env_list(sort_env.ph);
}

static int		check_is_key_in_env_list(t_data *data, t_env *sort_l,
										char *tmp, int *flag)
{
	while (sort_l)
	{
		if (!ft_strncmp(tmp, sort_l->key, (ft_strlen(tmp) + 1)))
		{
			(*flag)++;
			return (1);
		}
		sort_l = sort_l->next;
	}
	return (0);
}

static void		change_data_in_env_value(t_env *sort_l,
											char **tmp, const int i, int *flag)
{
	while (sort_l)
	{
		if (!ft_strncmp(tmp[i], sort_l->key, (ft_strlen(tmp[i]) + 1)))
		{
			free(sort_l->value);
			sort_l->value = ft_strdup(tmp[i + 1]);
			(*flag)++;
		}
		sort_l = sort_l->next;
	}
}

static void		add_env_in_env_list(t_data *data, t_env *sort_l, char **tmp)
{
	int		i;
	int		flag;

	i = 1;
	while (tmp[i])
	{
		flag = 0;
		sort_l = data->env_list;
		if ((i % 2) != 0 && (!ft_strncmp("0", tmp[i], 1)))
		{
			i++;
			if ((check_is_key_in_env_list(data, sort_l, tmp[i], &flag)) == 1)
				break ;
			if (!flag)
				LSTADD(&data->env_list, LSTNEW(DUP(tmp[i]), NULL));
			i++;
		}
		else
		{
			change_data_in_env_value(sort_l, tmp, i, &flag);
			if (!flag)
				LSTADD(&data->env_list, LSTNEW(DUP(tmp[i]), DUP(tmp[i + 1])));
			i += 2;
		}
	}
}

void			ft_export(t_data *data)
{
	t_env		*sort_l;
	char		**tmp;

	tmp = process_export(data->ar);
	sort_l = NULL;
	if (!data->ar[1])
		print_env_list(data, sort_l);
	else
		add_env_in_env_list(data, sort_l, tmp);
	free_2d_array(tmp);
}
