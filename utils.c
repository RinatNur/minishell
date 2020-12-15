#include "minishell.h"

void		ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env        *last;

	last = *lst;
	if (!last)
		*lst = new;
	else if (*lst && new)
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->prev = last;
		new->next = NULL;
	}
}

t_env		*ft_lstnew_env(void *key, void *value)
{
	t_env    *new_el;

	if ((new_el = malloc(sizeof(t_env))))
	{
		new_el->key = key;
		new_el->value = value;
		new_el->next = NULL;
		new_el->prev = NULL;
		return (new_el);
	}
	return (NULL);
}

int		ft_lstsize_env(t_env *lst)
{
	int		n;

	n = 0;
	while (lst)
	{
		lst = lst->next;
		n++;
	}
	return (n);
}

