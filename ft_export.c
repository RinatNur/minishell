#include "minishell.h"

t_env_list		*sort_env_list(t_sort_env *data)
{
//    t_env_list *ph = th;
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
    t_env_list  *sort_l;
    char        *ar_key;
    char        *ar_val;


    sort_env.ph = copy_list(data->env_list);
    sort_l = sort_env_list(&sort_env);
    if (data->ar[1])    //if array is empty print all env_sort_list
        while(sort_l)
        {
            ft_write(1, "declare -x ");
            ft_write(1, sort_l->key);
            ft_write(1, "=\"");
            ft_write(1, sort_l->value);
            ft_write(1, "\"");
            sort_l = sort_l->next;
            if (sort_l)
                ft_write(1, "\n");
        }
//    else
//    {
//        while ()
//    }
//    print_list_from_front(sort_l);

}
