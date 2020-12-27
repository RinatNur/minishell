//#include <minishell.h>
//
//void		ft_lstadd_back_new(t_list **lst, t_list *new)
//{
//	t_list        *last;
//
//	last = *lst;
//	if (!last)
//		*lst = new;
//	else if (*lst && new)
//	{
//		while (last->next != NULL)
//			last = last->next;
//		last->next = new;
//		new->next = NULL;
//	}
//}
//
//t_list		*ft_lstnew_new(void *cont)
//{
//	t_list    *new_el;
//
//	if ((new_el = malloc(sizeof(t_list))))
//	{
//		new_el->cont = cont;
//		new_el->next = NULL;
//		return (new_el);
//	}
//	return (NULL);
//}
//
//t_redirect		*redirect_constructor(t_type type, char *file)
//{
//	t_redirect		*redir;
//
//	if (!(redir = malloc(sizeof(t_redirect))))
//		ft_error("Malloc error", 6);
//	redir->redirect_type = type;
//	redir->filename = file;
//	return (redir);
//}
//
//void 	fill_t_redirect(t_list **list)
//{
//	t_redirect		*redir;
//
//	int 			i = 0;
//	redir = redirect_constructor(into_file, "a");
//	ft_lstadd_back_new(list, ft_lstnew_new(redir));
//	redir = redirect_constructor(into_file, "b");
//	ft_lstadd_back_new(list, ft_lstnew_new(redir));
//	redir = redirect_constructor(from_file, "test1");
//	ft_lstadd_back_new(list, ft_lstnew_new(redir));
//}
