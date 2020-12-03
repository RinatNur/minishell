#include "minishell.h"


int     main(int ac, char **av, char **envp) {
    t_data      data;
    t_env_list  *list;
    t_env_list  *sort_l;
    t_sort_env  sort_env;
    char        *pwd;
    int         pid;
    int         size_of_env;
    char        **env;
    int         i = 0, j;
    char        *path;
    char        *command = "export";
    char*        arr[] = { command,  "0", "sdf", "0", "RINAT", "EMPTY", "\0", "ddd", "123", NULL };

    list = NULL;
    data.ar = arr;
    data.cmd = command;
    env = env_copy(&data, (const char **)envp);
    make_env_list(&data, (const char **)env);
//    ft_export(&data);
//    print_list(data.env_list);
//    ft_export(&data);
//    list = cut_list(&data);
//    data.env_list = list;
//    print_list(data.env_list);
//    path = get_value_from_env(&data, "PWD");
//    pwd = ft_pwd();
//    path = ft_find_path(&data, command);
//    ft_write(1, path);
//    ft_exec(&data, path, arr, env);
    check_command(&data, command, env);
    data.ar[0] = command;
    data.ar[1] = NULL;
    ft_export(&data);
    return(0);
    //lists functions test
//    list = NULL;
//    ft_lstadd_back_dbl(&list, ft_lstnew_dbl("1 list", "1 end"));
//    ft_lstadd_back_dbl(&list, ft_lstnew_dbl("2 list", "2 end"));
//    ft_lstadd_back_dbl(&list, ft_lstnew_dbl("3 list", "3 end"));
//    print_list_from_front(list);
////    printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->value);
////    print_list_from_back(list);
//    printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->value);
//    while (NULL != list->next)
//    {
//        printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->value);
//        list = list->next;
//        if(NULL == list->next)
//            printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->value);
//    }
//    printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->value);
////    while (NULL != list->prev)
////    {
////        printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->value);
////        list = list->prev;
////    }
////    printf("key = %s  cont = %s\n", (char *)list->key, (char *)list->value);
////    return 0;
}