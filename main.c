#include "minishell.h"
//
int     main(int ar, char **av, char **envp)
{
    int i = 0, j;
    char *pwd;
    char   **env_copy;
    int     pid;
    int size_of_env;


    while (envp[i])
        i++;
    env_copy = (char **)malloc((i+1) * sizeof(char **));
//    env_copy = envp;
    i = 0;
    while (envp[i])
    {
        env_copy[i] = envp[i];
        i++;
    }
    env_copy[i] = NULL;
    size_of_env = i;
//    env_copy[i] = NULL;

    char* arr[3];
//    arr[0] = "-e";
//    arr[1] = "Makefile";
//    arr[1] = "-l";
    arr[0] = NULL;
//        write(1, "HELLO\n", 6);
    int err = execve("/bin/sh", arr, NULL);
    if (err == -1)
        {
            printf("FAILURE\n");
            printf("errno = %d\n", errno);
            return (err);
        }

    pid = fork();
    if (pid == -1)
        return (1);

    i = 0;
//    pwd = ft_pwd();
//    int file = open("../test.c", O_WRONLY | O_CREAT, 0777);
//    dup2(file, STDOUT_FILENO);
//    printf("%s", pwd);
//    ft_env(env_copy, size_of_env);
    if(pid == 0)
    {
        char* arr[] = { NULL };
//        write(1, "HELLO\n", 6);
        int err = execve("ls", arr, env_copy);
        if (err == -1)
        {
            printf("FAILURE\n");
            return (err);
        }

    }
    else
    {
        int     wait_status = 0;
        wait (&wait_status);
        if (WIFEXITED(wait_status))
        {
            int status_code = WEXITSTATUS(wait_status);
//            if (status_code == 0)
////                printf("sucess");
//            else
//                printf("failure with the status code %d\n", status_code);
        }
    }
}

int     main(int ar, char **av, char **envp) {
    t_data      data;
    t_env_list  *list;
    char        **env;
    int         i = 0;

    env = env_copy((const char **)envp);
//    while (env[i])
//    {
//        write(1, env[i], ft_strlen(env[i]));
//        write(1, "\n", 1);
//        i++;
//    }
    list = make_env_list(&data, (const char **)envp);
//    print_list_from_back(list);
//    write(1, data.env_pwd, ft_strlen(data.env_pwd));
//    write
    write(1, data.env_pwd, ft_strlen(data.env_pwd));

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