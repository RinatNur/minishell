#include <minishell.h>

void		ft_lstadd_back_new(t_list_new **lst, t_list_new *new)
{
	t_list_new        *last;

	last = *lst;
	if (!last)
		*lst = new;
	else if (*lst && new)
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->next = NULL;
	}
}

t_list_new		*ft_lstnew_new(void *cont)
{
	t_list_new    *new_el;

	if ((new_el = malloc(sizeof(t_list_new))))
	{
		new_el->cont = cont;
		new_el->next = NULL;
		return (new_el);
	}
	return (NULL);
}

t_redirect		*redirect_constructor(t_type type, char *file)
{
	t_redirect		*redir;

	if (!(redir = malloc(sizeof(t_redirect))))
		ft_error("Malloc error", 6);
	redir->redirect_type = type;
	redir->filename = file;
	return (redir);
}

void 	fill_t_redirect(t_list_new **list)
{
	t_redirect		*redir;

	int 			i = 0;
	redir = redirect_constructor(into_file, "aaa");
	ft_lstadd_back_new(list, ft_lstnew_new(redir));
	redir = redirect_constructor(into_file, "bbb");
	ft_lstadd_back_new(list, ft_lstnew_new(redir));
	redir = redirect_constructor(from_file, "ccc");
	ft_lstadd_back_new(list, ft_lstnew_new(redir));
}

