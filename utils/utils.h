//
// Created by Wolmer Rudy on 12/7/20.
//

#ifndef MINISHELL_UTILS_H
#define MINISHELL_UTILS_H
#include "stdlib.h"
#include "unistd.h"

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);

void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void*));
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);

int					u_strlen(const char *str);
char				*u_strdup(const char *s);
char				**u_split(char const *s, char c, const char *mask);
char				*get_mask(char *line);
void				free_2d_array(void **array);
void				empty_lst_clear(t_list **lst);
char				*empty_str(char c, int len);
int					find_char(const char *str, char c);
char				**process_export_arg(char *export_arg);
char **process_export(char **export_with_arguments);


#endif //MINISHELL_UTILS_H
