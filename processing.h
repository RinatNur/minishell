#ifndef PROCESSING_H
#define PROCESSING_H

#define ERR1 No such file or directory
# define REDIR ((t_redirect *)(data->redirect_list->cont))

typedef struct			s_env {
	void                *key;
	void                *value;
	struct s_env        *next;
	struct s_env        *prev;
}						t_env;

typedef struct            s_sort_env {
	t_env              *ph;
	t_env              *out;
	t_env              *p;
	t_env              *pr;
	t_env              *q;
}                         t_sort_env;

typedef struct			s_conv {
	int					type;
	char				**ar;
	struct s_conv		*next;
	struct s_conv		*prev;
}						t_conv;

typedef struct      s_data {
	t_list		*redirect_list;
	t_env			*env_list;
	char 			**ar;//TODO delete after ending parser
	char 			*wr_file_name;
	int 			wr_type_redir;
	char 			*rd_file_name;
}                   t_data;


void            *ft_pwd();
void            ft_env(t_data *data);
char            *ft_find_path(t_data *data, char *command);
void            print_list(t_env *list);

void            make_env_list(t_data *data, const char **env);
char            **env_copy(t_data *data, const char **envp);
int				ft_exec(t_data *data);
void            check_command(t_data *data);
void            ft_error(char *str, int code);
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

#endif //MINISHELL_GIT_MY_PROCESSING_H
