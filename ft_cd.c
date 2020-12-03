#include "minishell.h"

void    ft_cd(t_data *data)
{
    t_env_list      *list;
    char            *tmp;
    int             flag = 0;

    list = data->env_list;
    if (!data.ar[1])
        (chdir(path) == -1) ? ft_error("Chdir can't change the directory", 5) : 0;
    while (list)
    {
        if ((!ft_strncmp("PWD", list->key, 4)))
        {
            tmp = list->key;
            list->key = data->ar[1];
        }
        else if ((!ft_strncmp("OLDPWD", list->key, 7)))
        {
            list->key = tmp;
            flag++;
        }
        if (!flag && !list->next)
            ft_lstadd_back_dbl(list)
        list = list->next;
    }
}

