#include "processing.h"
#include "./utils/utils.h"

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

static void 		print_env_list(t_data *data, t_env *sort_l)
{
	t_sort_env  sort_env;

	sort_env.ph = copy_list(data->env_list);
	sort_l = sort_env_list(&sort_env);

	while(sort_l)
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

static void 			change_data_in_env_value(t_data *data, t_env *sort_l, char **tmp, int *flag)
{
	while (sort_l)
	{
		if (!ft_strncmp(*tmp, sort_l->key, (ft_strlen(*tmp) + 1)))
		{
			free(sort_l->value);
			sort_l->value = ft_strdup(*(tmp + 1));
			(*flag)++;
		}
		if (!flag)
			ft_lstadd_back_env(&data->env_list, ft_lstnew_env(ft_strdup(*tmp), ft_strdup(*(tmp + 1))));
		sort_l = sort_l->next;
	}
}

static int 				check_is_key_in_env_list(t_data *data, t_env *sort_l, char *tmp, int *flag)
{
	while(sort_l)
	{
		if (!ft_strncmp(tmp, sort_l->key, (ft_strlen(tmp) + 1)))
		{
			(*flag)++;
			return (1);
		}
		if (!flag)
			ft_lstadd_back_env(&data->env_list, ft_lstnew_env(ft_strdup(tmp), NULL));
		sort_l = sort_l->next;
	}
	return (0);
}

//static

void    ft_export(t_data *data)
{
    t_env		*sort_l;
    int         i;
    int 		flag;
    char        **tmp;

	i = 1;
	sort_l = NULL;
    if (!data->ar[1])
       	print_env_list(data, sort_l);
    else
    {
        tmp = process_export(data->ar);
        while (tmp[i])
        {
    		flag = 0;
			sort_l = data->env_list;
        	if ((i % 2) != 0 && (!ft_strncmp("0", tmp[i], 1)))
			{
        		i++;
        		if ((check_is_key_in_env_list(data, sort_l, tmp[i], &flag)) == 1)
        			break ;
        		i++;
			}
        	else
			{
        		change_data_in_env_value(data, sort_l, &(tmp[i]), &flag);
				i += 2;
			}
		}
		free_2d_array(tmp);
	}
}
