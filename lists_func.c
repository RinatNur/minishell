#include "minishell.h"

t_list      *copy_list(t_list *list)
{
    t_list      *tmp;

    tmp = NULL;
    while (list)
    {
        ft_lstadd_back(&tmp, ft_lstnew(list->key, list->value));
        list = list->next;
    }
    return (tmp);
}

t_list      *cut_list(t_data *data, char *ar)
{
    t_list      *list;
    t_list      *tmp;

    list = data->env_list;
    size_t len = ft_strlen(ar) + 1;
    while (list->next)
    {
        if (!ft_strncmp(ar, list->key, len))
        {
            if (list->prev == NULL)
            {
                list = list->next;
                list->prev = NULL;
            }
            else if (list->next != NULL)
            {
                tmp = list->prev;
                list = list->next;
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
            list = list->prev;
            list->next = NULL;
        }
    return (list);
}

void            print_list(t_list *list)
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
