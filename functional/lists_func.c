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
		while (data->p && (ft_strncmp(data->p->key, data->q->key, (ft_strlen(data->q->key) + 1))) < 0)
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

t_env      *copy_list(t_env *list)
{
    t_env		*tmp;

    tmp = NULL;
    while (list)
    {
    	if(list->value == NULL)
			ft_lstadd_back_env(&tmp,ft_lstnew_env(ft_strdup(list->key), NULL));
    	else
			ft_lstadd_back_env(&tmp, ft_lstnew_env(ft_strdup(list->key), ft_strdup(list->value)));
		list = list->next;
	}
	return (tmp);
}

t_env      *cut_list(t_data *data, char *ar)
{
	t_env      *list;
	t_env      *tmp;

	list = data->env_list;
	size_t len = ft_strlen(ar) + 1;
	while (list->next)
	{
		if (!ft_strncmp(ar, list->key, len))
		{
			if (list->prev == NULL)
			{
				tmp = list;
				list = list->next;
				free_env_content(tmp);
				free(tmp);

				list->prev = NULL;
			}
			else if (list->next != NULL)
			{
				tmp = list->prev;


				list = list->next;

				free_env_content(list->prev);
				free(list->prev);

				list->prev = tmp;
				tmp->next = list;
				break ;
			}
		}
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
    data->env_list = list;
    while (data->env_list->prev)
       	data->env_list = data->env_list->prev;
    return (data->env_list);
}

void            print_list(t_env *list)
{
    int     i = 0;

    if (list && list->next == NULL)
        while (list->prev)
            list = list->prev;

    while (NULL != list)
    {
        printf("%d. %s=%s\n", i++, (char *)list->key, (char *)list->value);
        list = list->next;
    }
}
