#include "minishell.h"


int     main(int ac, char **av, char **envp) {
	t_conv		conv;
    t_data      data;
	char  	list[1000];
	t_list  	*sort_l;
	char		*command = "ls";
	char*		arr[] = { command, "/Users/jheat", "-l", NULL };
	int 		file;
	enum e_type	type;
//	t_list_new 		*list_new = NULL;
//    redirect_list = list_new;
//	t_list_new		*redirect_list = NULL;

	data.redirect_list = NULL;
	//TODO try to send conv to the pipe;
    data.ar = arr;
    make_env_list(&data, (const char **)envp);
//    fill_t_redirect(&data.redirect_list);
//	ft_check_redirects(&data);

//	ft_redirect_read(&data);
//    while (data.redirect_list)
//	{
//    	printf("%s", ((t_redirect *)(data.redirect_list->cont))->filename);
////		unsigned test;
////		test = (((t_redirect *)(redirect_list->cont))->redirect_type) + '0';
////		write(1, &test, 1);
//		data.redirect_list = data.redirect_list->next;
//		if (data.redirect_list)
//			printf("\n");
//	}

//    list = get_value_from_env(&data, "PATH");
//	ft_redirect_write(&data);
//	file = open("test.txt", O_WRONLY | O_CREAT, 0777);
//	ft_pipe(&data);

	check_command(&data);
//	write(1, "sgasg", 9);
//	list[999] = '\0';
//	command = "grep";
//    data.ar[0] = command;
//    data.ar[1] = "test.txt";
//    data.ar[2] = NULL;

//	ft_pipe(&data);
//	ft_pipe(&data);
//	ft_pipe(&data);
//	ft_pipe(&data);
//	check_command(&data);
    return(0);
}