#include "minishell.h"

//t_env_list		*sort_spr(t_sort_env *data, t_env_list **ph)
//{
//    data->out = NULL;
//    while (*ph)
//    {
//        data->q = *ph;
//        *ph = (*ph)->next;
//        data->p = data->out;
//        data->pr = NULL;
//        while (data->p && (ft_strncmp(data->q.key, data->p.key, (ft_strlen(data->q.key) + 1))) < 0)
//        {
//            data->pr = data->p;
//            data->p = data->p.next;
//        }
//        if (data->pr == NULL)
//        {
//            data->q.next = data->out;
//            data->out = data->q;
//        }
//        else
//        {
//            data->q.next = data->p;
//            data->pr.next = data->q;
//        }
//    }
//    *ph = data->out;
//    return (*ph);
//}
//
//void    ft_export(t_data *data)
//{
//
//}
