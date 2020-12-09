//
// Created by Wolmer Rudy on 12/7/20.
//

#ifndef MINISHELL_UTILS_H
#define MINISHELL_UTILS_H
#include "stdlib.h"

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

int					ft_strlen(const char *str);
char				*ft_strdup(const char *s);
char				**ft_split(char const *s, char c);

#endif //MINISHELL_UTILS_H
