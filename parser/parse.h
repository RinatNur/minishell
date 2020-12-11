#ifndef MINISHELL_PARSE_H
#define MINISHELL_PARSE_H
#include "utils/utils.h"
#include "stdio.h"

/*
** command
*/
typedef enum		e_flag
{
	false,
	true
}					t_flag;


typedef enum		e_type
{
	from_file,
	into_file,
	into_file_with_rewrite
}					t_type;

typedef struct		s_redirect
{
	t_type			redirect_type;
	char			*filename;
}					t_redirect;

typedef struct		s_command
{
	char			**command_with_arguments;
	char 			*tmp; 										//FIXME сделать список редиректов полноценным списком
	//t_list			*redirect_list;
}					t_command;

t_list				*parse(char *command_line);
t_command			*parse_command(const char *command_str);

#endif //MINISHELL_PARSE_H
