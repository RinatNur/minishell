//
// Created by Wolmer Rudy on 12/7/20.
//

#ifndef MINISHELL_UTILS_H
#define MINISHELL_UTILS_H
#include "stdlib.h"
#include "minishell.h"


t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);

void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void*));
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);
char				*u_strjoin(char const *s1, char const *s2);
char 				*arr_strjoin(char **line);
char				*u_strldup(const char *s, size_t l);

int					u_strlen(const char *str);
char				*u_strdup(const char *s);
char				**u_split(char const *s, char c, const char *mask);
char				*get_mask(char *line);
void				free_2d_array(char **array);
void				empty_lst_clear(t_list **lst);
char				*empty_str(char c, int len);

char **parse_env(char *arg);


#endif //MINISHELL_UTILS_H
