#ifndef MINISHELL_UTILS_H
#define MINISHELL_UTILS_H

#include "minishell.h"

t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);

void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void*));
t_list				*ft_lstlast(t_list *lst);
int					ft_lstsize(t_list *lst);

int					ft_strlen_pars(const char *str);
char				*ft_strdup_pars(const char *s);
char				**ft_split_mask(char const *s, char c, const char *mask);
char				*get_mask(char *line);
void				free_2d_array(void **array);
void				empty_lst_clear(t_list **lst);
char				*empty_str(char c, int len);


#endif //MINISHELL_UTILS_H

