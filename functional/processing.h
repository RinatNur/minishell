#ifndef PROCESSING_H
#define PROCESSING_H

#include "../libft/libft.h"
#include "../minishell.h"

#define ERR1 No such file or directory
# define MSHELL "-minishell"
# define REDIR ((t_redirect *)(data->redirect_list->content))

typedef struct            s_sort_env {
	t_env              *ph;
	t_env              *out;
	t_env              *p;
	t_env              *pr;
	t_env              *q;
}                         t_sort_env;

void            *ft_pwd();
void            ft_env(t_data *data);
char            *ft_find_path(t_data *data, char *command);
void            print_list(t_env *list);

void            make_env_list(t_data *data, const char **env);
char            **env_copy(t_data *data, const char **envp);
int				ft_exec(t_data *data);
void            check_command(t_data *data);
void            ft_error(char *str, int code);
void			ft_error_stderr(char *str, int code);
ssize_t         ft_write(int fd, const void *buf);
void            ft_echo(t_data *data);
char            *get_value_from_env(t_data *data, char *key);
t_env			*sort_env_list(t_sort_env *data);
void            ft_export(t_data *data);
t_env			*copy_list(t_env *list);
void			ft_unset(t_data *data);
t_env			*cut_list(t_data *data, char *ar);
void			ft_cd(t_data *data);
void			ft_exit();
char			**list_to_mas_ref(t_data *data);
void			ft_pipe(t_data *data);
void			ft_redirect_write(t_data *data);
void			ft_redirect_read(t_data *data);
void			ft_redirect_read(t_data *data);
int 			ft_check_redirects(t_data *data);
void			ft_lstadd_back_env(t_env **lst, t_env *new);
t_env			*ft_lstnew_env(void *key, void *value);
int				ft_lstsize_env(t_env *lst);
void			fill_t_redirect(t_list **list);
void			ft_error_print(char *minishell, char *command, char *filename, char *message);
void			ft_pipe_eof(void);
void			ft_redirect_read_pipe(t_data *data);

#endif
