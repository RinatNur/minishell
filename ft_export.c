#include "minishell.h"

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

void    ft_export(t_data *data)
{
    t_sort_env  sort_env;
    t_env		*sort_l;
    int         i;
    int 		flag;

	i = 1;
	flag = 0;
    if (!data->ar[1])//if array is empty print all env_sort_list
    {
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
//            if (sort_l)TODO ask if it nesessary \n at the end of output
                ft_write(1, "\n");
        }
    }
    else
    {
    	sort_l = data->env_list;
        while (data->ar[i])
        {
        	if ((i % 2) != 0 && (!ft_strncmp("0", data->ar[i], 1))) //if odd value of arr = 0 -> key = NULL
				ft_lstadd_back_env(&data->env_list, ft_lstnew_env(data->ar[i + 1], NULL));
        	else
			{
        		while(sort_l)
        		{
        			if (!ft_strncmp(data->ar[i], sort_l->key, (ft_strlen(data->ar[i]) + 1)))
        			{
        				sort_l->key = data->ar[i];
        				sort_l->value = data->ar[i + 1];
        				flag++;
        				break ;
        			}
        			sort_l = sort_l->next;
        		}
        		if (!flag)
					ft_lstadd_back_env(&data->env_list, ft_lstnew_env(data->ar[i], data->ar[i + 1]));
			}
            i += 2;
        }
    }
}
