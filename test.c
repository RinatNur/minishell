#include <stdlib.h>
#include <stdio.h>
typedef struct            s_env_list {
    void                     *key;
    void                     *content;
    struct s_env_list        *next;
    struct s_env_list        *prev;
}                         t_env_list;

t_env_list        *ft_dbl_lstnew(void *key, void *content)
{
    t_env_list    *new_el;

    if ((new_el = malloc(sizeof(t_env_list))))
    {
        new_el->key = key;
        new_el->content = content;
        new_el->next = NULL;
        new_el->prev = NULL;
        printf("key = %s  cont = %s\n", (char *)new_el->key, (char *)new_el->content);
        return (new_el);
    }
    return (NULL);
}

//int main() {
//  t_env_list  *list;
//  char  *key = "PATH";
//  char  *cont = "/bin/";
//  list = ft_dbl_lstnew(key, cont);
////  printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->content);
//  return 0;
//}