#ifndef PROCESSING_H
#define PROCESSING_H

#define ERR1 No such file or directory

//typedef struct			s_env {
//	void				*key;
//	void				*value;
//	struct s_env		*next;
//	struct s_env		*prev;
//}						t_list;

typedef struct            s_sort_env {
	t_list              *ph;
	t_list              *out;
	t_list              *p;
	t_list              *pr;
	t_list              *q;
}                         t_sort_env;

typedef struct			s_conv {
	int					type;
	char				**ar;
	struct s_conv		*next;
	struct s_conv		*prev;
}						t_conv;

typedef struct      s_data {
	t_list			*env_list;
	t_conv			conv;
	char			**ar;
}                   t_data;


void            *ft_pwd();
void            ft_env(t_data *data);
char            *ft_find_path(t_data *data, char *command);
void            print_list(t_list *list);

void            make_env_list(t_data *data, const char **env);
char            **env_copy(t_data *data, const char **envp);
int				ft_exec(t_data *data);
void            check_command(t_data *data);
void            ft_error(char *str, int code);
ssize_t         ft_write(int fd, const void *buf);
void            ft_echo(t_data *data);
char            *get_value_from_env(t_data *data, char *key);
t_list			*sort_env_list(t_sort_env *data);
void            ft_export(t_data *data);
t_list			*copy_list(t_list *list);
void			ft_unset(t_data *data);
t_list			*cut_list(t_data *data, char *ar);
void			ft_cd(t_data *data);
void			ft_exit();
char			**list_to_mas_ref(t_data *data);

#endif //MINISHELL_GIT_MY_PROCESSING_H
