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

void        print_list_from_front(t_env_list *list)
{
    while (NULL != list->next)
    {
        printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->value);
        list = list->next;
        if(NULL == list->next)
            printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->value);
    }
}

void            print_list_from_back(t_env_list *list)
{
    while (NULL != list->next)
        list = list->next;
    while (NULL != list->prev)
    {
        printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->value);
        list = list->prev;
        if(NULL == list->prev)
            printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->value);
    }
}
