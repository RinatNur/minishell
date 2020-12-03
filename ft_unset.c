#include "minishell.h"

void    ft_unset(t_data *data, char *ar)
{
    t_env_list      *list;
    int             i = 0;
    size_t          len;

    list = data->env_list;
    len = ft_strlen(ar) + 1;
    while (list)
    {
        if (!ft_strncmp(ar, list->key, len))
        {
            cut_list(data, ar);
            break ;
        }
        list = list->next;
    }
}

