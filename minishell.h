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

#define ERR1 No such file or directory

typedef struct            s_env_list {
    void                     *key;
    void                     *value;
    struct s_env_list        *next;
    struct s_env_list        *prev;
}                         t_env_list;

typedef struct            s_sort_env {
    t_env_list              *ph;
    t_env_list              *out;
    t_env_list              *p;
    t_env_list              *pr;
    t_env_list              *q;
}                         t_sort_env;

typedef struct      s_data {
    t_env_list          *env_list;
    char                **env;
    char                **ar;
    char                *cmd;
    int                 env_len;
}                   t_data;


void            *ft_pwd();
//size_t          ft_strlen(const char *s);
void            ft_env(t_data *data);
char            *ft_find_path(t_data *data, char *command);
t_env_list      *ft_lstnew_dbl(void *key, void *content);
void            ft_lstadd_back_dbl(t_env_list **lst, t_env_list *new);
void            print_list(t_env_list *list);

void            make_env_list(t_data *data, const char **env);
char            **env_copy(t_data *data, const char **envp);
int             ft_exec(t_data *data, char *path, char **arr, char **env);
void            check_command(t_data *data, char *command,  char **env);
void            ft_error(char *str, int code);
ssize_t         ft_write(int fd, const void *buf);
void            ft_echo(t_data *data);
char            *get_value_from_env(t_data *data, char *key);
t_env_list		*sort_env_list(t_sort_env *data);
void            ft_export(t_data *data);
t_env_list      *copy_list(t_env_list *list);
void            ft_unset(t_data *data);
t_env_list      *cut_list(t_data *data);
#endif