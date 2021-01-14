/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 20:51:10 by jheat             #+#    #+#             */
/*   Updated: 2021/01/13 20:51:12 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

void		ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env		*last;

	last = *lst;
	if (!last)
		*lst = new;
	else if (*lst && new)
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->prev = last;
		new->next = NULL;
	}
}

t_env		*ft_lstnew_env(void *key, void *value)
{
	t_env		*new_el;

	if ((new_el = malloc(sizeof(t_env))))
	{
		new_el->key = key;
		new_el->value = value;
		new_el->next = NULL;
		new_el->prev = NULL;
		return (new_el);
	}
	return (NULL);
}

int			ft_lstsize_env(t_env *lst)
{
	int		n;

	n = 0;
	while (lst)
	{
		lst = lst->next;
		n++;
	}
	return (n);
}

ssize_t		ft_write(int fd, const void *buf)
{
	int		len;
	int		ret;

	len = ft_strlen(buf);
	((ret = write(fd, buf, len)) == -1)
					? ft_error("Error in function write", 3) : 0;
	return (ret);
}

char		*get_value_from_env(t_data *data, char *key)
{
	t_env		*list;

	list = data->env_list;
	while (list)
	{
		if (!ft_strncmp(list->key, key, (ft_strlen(list->key) + 1)))
			return (list->value);
		list = list->next;
	}
	return (NULL);
}

char				*get_pwd(void)
{
	char *dir;

	dir = NULL;
	dir = getcwd(dir, 0);
	return (dir);
}
