#ifndef MINISHELL_PARSE_H
#define MINISHELL_PARSE_H
#include "../utils/utils.h"
#include "stdio.h"

typedef enum		e_rtype
{
	from_file,
	into_file,
	into_file_with_rewrite
}					t_rtype;

typedef struct		s_redirect
{
	t_rtype			redirect_type;
	char			*filename;
}					t_redirect;
t_redirect			*redirect_constructor(t_rtype redirect_type, char *filename);
void 				redirect_destructor(t_redirect *redirect);

typedef struct		s_command
{
	char			**command_with_arguments;
	t_list			*redirect_list;
}					t_command;
t_command			*command_constructor(char **command_with_arguments, t_list *redirect_list);
void 				command_destructor(t_command *command);

t_command			*parse_command(const char *command_str);
t_list				*parse_pipeline_list(char *command_line);
void				free_pipeline_list(t_list *pipeline_list);

#endif
