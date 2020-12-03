#include "minishell.h"

t_env_list        *ft_lstnew_dbl(void *key, void *content)
{
    t_env_list    *new_el;

    if ((new_el = malloc(sizeof(t_env_list))))
    {
        new_el->key = key;
        new_el->value = content;
        new_el->next = NULL;
        new_el->prev = NULL;
        return (new_el);
    }
    return (NULL);
}

void        ft_lstadd_back_dbl(t_env_list **lst, t_env_list *new)
{
    t_env_list        *last;

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

void		ft_lstadd_front_dbl(t_list **lst, t_list *new)
{
//    if (lst && new)
//    {
//        new->next = *lst;
//        *lst = new;
//        *lst->prev = new;
//    }
}

t_env_list      *copy_list(t_env_list *list)
{
    t_env_list      *tmp;

    tmp = NULL;
    while (list)
    {
        ft_lstadd_back_dbl(&tmp, ft_lstnew_dbl(list->key, list->value));
        list = list->next;
    }
    return (tmp);
}

t_env_list      *cut_list(t_data *data)
{
    t_env_list      *list;
    t_env_list      *tmp;

    list = data->env_list;
    size_t len = ft_strlen(data->cmd) + 1;
    while (list->next)
    {
        if (!ft_strncmp(data->cmd, list->key, len))
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
            }
        }

        list = list->next;
    }
    if (!ft_strncmp(data->cmd, list->key, len))
        if (list->next == NULL)
        {
            list = list->prev;
            list->next = NULL;
        }
//    list = list->prev;
//    printf("%s\t%s", list->key, list->value);
//    print_list_from_back(list);
    return (list);
}

void            print_list(t_env_list *list)
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
