#ifndef MINISHELL_PARSE_H
#define MINISHELL_PARSE_H
#include "../utils/utils.h"
#include "stdio.h"


t_redirect			*redirect_constructor(t_rtype redirect_type, char *filename);
void 				redirect_destructor(t_redirect *redirect);


t_command			*command_constructor(char **command_with_arguments, t_list *redirect_list);
void 				command_destructor(t_command *command);

t_command			*parse_command(const char *command_str);
t_list		        *parse_redirects(char **command, t_command *cmd);
t_list				*parse_pipeline_list(char *command_line);
void				free_pipeline_list(t_list *pipeline_list);

#endif
