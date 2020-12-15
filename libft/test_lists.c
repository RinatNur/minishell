#include <stdlib.h>
#include <stdio.h>

typedef struct            s_env_list {
    void                     *key;
    void                     *value;
    struct s_env_list        *next;
    struct s_env_list        *prev;
}                         t_env_list;

typedef struct      s_data {
    t_env_list          *env_list;
}                   t_data;

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

void        ft_lstadd_back_dbl(t_env_list *lst, t_env_list *new)
{
    t_env_list        *last;

    last = lst;
    if (!last)
        lst = new;
    else if (last && new)
    {
        while (last->next)
            last = last->next;
        last->next = new;
        new->prev = last;
        new->next = NULL;
    }
}

void            print_list(t_env_list *list)
{
    int     i = 0;
    // t_env_list    *list;
    
    // list = *lst;
    if (list && list->next == NULL)
        while (list->prev)
            list = list->prev;

    while (NULL != list)
    {
        printf("%d. %s=%s\n", i++, (char *)list->key, (char *)list->value);
        list = list->next;
    }
    // lst = list;
}

// char      **env_copy(t_data *data, const char **envp)
// {
//     char    **env;
//     int     i = 0;
//     int     len_str;
        
//     while (envp[i])
//         i++;
//     env = malloc((i + 1) * sizeof(char *));
//     env[i] = NULL;
//     i = 0;
//     while (envp[i])
//     {
//         len_str = ft_strlen(envp[i]);
//         env[i] = malloc(len_str + 1);
//         env[i][len_str] = '\0';
//         env[i] = (char *)envp[i];
//         i++;
//     }
//     data->env = env;
//     return (env);
// }

int main(int ac, char **av, char **envp) {
t_data      data;
t_env_list  *list;

list = ft_lstnew_dbl("USER", "jheat");
data.env_list = list;
// printf("list = %p\tenv_list = %p", list, data.env_list);
ft_lstadd_back_dbl(list, ft_lstnew_dbl("PATH", "/bin/"));

// list = env_copy(&data, envp);
// data.env_list = data.env_list->next;
// data.env_list = data.env_list->next;
// printf("%s\t%s", data.env_list->key, data.env_list->value);
print_list(list);
printf("\n");
print_list(data.env_list);
return 0;
}
