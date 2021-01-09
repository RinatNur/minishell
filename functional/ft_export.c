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

void    ft_export(t_data *data)
{
    t_sort_env  sort_env;
    t_env		*sort_l, *tmp_env;
    int         i;
    int 		flag;
    char        **tmp;

    tmp_env = data->env_list;
	i = 1;
    if (!data->ar[1])//if array is empty print all env_sort_list
    {
        sort_env.ph = tmp_env;
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
    }
    else
    {
        tmp = process_export(data->ar);
        while (tmp[i])
        {
    		flag = 0;
//			sort_l = data->env_list;
        	if ((i % 2) != 0 && (!ft_strncmp("0", tmp[i], 1)))//if odd value of arr = 0 -> key = NULL
			{
        		i++;
				while(sort_l)
				{
					if (!ft_strncmp(tmp[i], sort_l->key, (ft_strlen(tmp[i]) + 1)))
					{
						flag++;
						break ;
					}
					sort_l = sort_l->next;
				}
				if (!flag)
					ft_lstadd_back_env(&sort_l, ft_lstnew_env(ft_strdup(tmp[i]), NULL));
				i++;
			}
        	else
			{
				while (sort_l)
				{
					if (!ft_strncmp(tmp[i], sort_l->key, (ft_strlen(tmp[i]) + 1)))
					{
						sort_l->value = ft_strdup(tmp[i + 1]);
						flag++;
						break;
					}
					sort_l = sort_l->next;
				}
				if (!flag)
					ft_lstadd_back_env(&sort_l, ft_lstnew_env(ft_strdup(tmp[i]), ft_strdup(tmp[i + 1])));
				i += 2;
			}
		}
		free_2d_array(tmp);
	}
    data->env_list = sort_l;
}

//export a; export a=; export a=b