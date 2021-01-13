/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:10:46 by jheat             #+#    #+#             */
/*   Updated: 2021/01/12 16:11:00 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

char				*get_pwd(void)
{
	char *dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	return (dir);
}

static void			chdir_to_home(t_data *data)
{
	free(data->ar[0]);
	free(data->ar);
	if (!(data->ar = malloc(sizeof(char *) * 3)))
		exit(EXIT_FAILURE);
	data->ar[0] = ft_strdup("cd");
	data->ar[1] = ft_strdup(get_value_from_env(data, "HOME"));
	data->ar[2] = NULL;
}

static int			print_value_oldpwd(t_data *data)
{
	char *oldpwd;

	if ((!ft_strncmp("-", data->ar[1], 2)))
	{
		oldpwd = get_value_from_env(data, "OLDPWD");
		if (oldpwd)
		{
			free(data->ar[1]);
			data->ar[1] = ft_strdup(oldpwd);
			ft_write(1, data->ar[1]);
			ft_write(1, "\n");
		}
		else
		{
			ft_error_print(MSHELL, data->ar[0], NULL, "OLDPWD not set");
			return (1);
		}
	}
	return (0);
}

static void			set_current_path(char *path, t_env *list, char *arg)
{
	if (path)
	{
		free(list->value);
		list->value = path;
	}
	else
	{
		free(list->value);
		list->value = ft_strdup(arg);
	}
}

static void			change_val_pwd_and_oldpwd(t_data *data,
												 t_env *list, t_env *list2, char *pwd_tmp)
{
	int			flag;

	flag = 0;
	while (list)
	{
		if ((!ft_strncmp("PWD", list->key, 4)))
		{
			(ft_strncmp("..", list->value, 3)) ? (pwd_tmp = get_pwd()) : 0;
			while (list2)
			{
				if ((!ft_strncmp("OLDPWD", list2->key, 7)))
				{
					free(list2->value);
					list2->value = ft_strdup(list->value);
					flag++;
					break ;
				}
				list2 = list2->next;
			}
			set_current_path(pwd_tmp, list, data->ar[1]);
		}
		list = list->next;
	}
}

void				ft_cd(t_data *data)
{
	t_env		*list;
	t_env		*list2;
	char		*pwd_tmp;

	pwd_tmp = NULL;
	list = data->env_list;
	list2 = data->env_list;
	if (!ft_strncmp("CD", data->ar[0], 3))
		return ;
	if (!data->ar[1])
		chdir_to_home(data);
	if (data->ar[1])
		if ((print_value_oldpwd(data)) == 1)
			return ;
	if (chdir(data->ar[1]) == -1)
		ft_error_print(MSHELL, data->ar[0], data->ar[1], strerror(errno));
	change_val_pwd_and_oldpwd(data, list, list2, pwd_tmp);
}
