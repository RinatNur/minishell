#ifndef MiNISHELL_H
# define MiNISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <./libft/libft.h>
#include <dirent.h>

typedef struct            s_env_list {
    void                     *key;
    void                     *content;
    struct s_env_list        *next;
    struct s_env_list        *prev;
}                         t_env_list;

typedef struct      s_data {
    t_env_list          env_list;
    char                *env_path;
    char                *env_pwd;
}                   t_data;


char            *ft_pwd();
size_t          ft_strlen(const char *s);
void            ft_env(char **env, int env_len);
char            *ft_find_path(char *command, char **env);
t_env_list      *ft_lstnew_dbl(void *key, void *content);
void            ft_lstadd_back_dbl(t_env_list **lst, t_env_list *new);
void            print_list_from_front(t_env_list *list);
void            print_list_from_back(t_env_list *list);

t_env_list      *make_env_list(t_data *data, const char **env);
char            **env_copy(const char **envp);

#endif