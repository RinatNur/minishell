#include "minishell.h"


int     main(int ar, char **av, char **envp) {
    t_data      data;
    t_env_list  *list;
    char        *pwd;
    int         pid;
    int         size_of_env;
    char        **env;
    int         i = 0, j;
    char        *path;
    char        *command = "env";
    char*        arr[] = { command, NULL };

    ft_write(1, "asfdfsdf");
//    ft_error("test message", 123);
//    env = env_copy(&data, (const char **)envp);
//    list = make_env_list(&data, (const char **)env);
//    path = ft_find_path(&data, command);
//    ft_exec(&data, path, arr, env);
//    check_command(&data, command, path, arr, env);
    //lists functions test
//    list = NULL;
//    ft_lstadd_back_dbl(&list, ft_lstnew_dbl("1 list", "1 end"));
//    ft_lstadd_back_dbl(&list, ft_lstnew_dbl("2 list", "2 end"));
//    ft_lstadd_back_dbl(&list, ft_lstnew_dbl("3 list", "3 end"));
//    print_list_from_front(list);
////    printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->content);
////    print_list_from_back(list);
//    printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->content);
//    while (NULL != list->next)
//    {
//        printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->content);
//        list = list->next;
//        if(NULL == list->next)
//            printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->content);
//    }
//    printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->content);
////    while (NULL != list->prev)
////    {
////        printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->content);
////        list = list->prev;
////    }
////    printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->content);
////    return 0;
}