/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:32:49 by wrudy             #+#    #+#             */
/*   Updated: 2021/01/14 19:32:51 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "gnl/get_next_line.h"
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>

int						g_code;
char					*g_buf;

typedef struct			s_list
{
	void				*content;
	struct s_list		*next;
}						t_list;

typedef enum			e_rtype
{
	from_file,
	into_file,
	into_file_with_rewrite
}						t_rtype;

typedef struct			s_redirect
{
	t_rtype				redirect_type;
	char				*filename;
}						t_redirect;

typedef struct			s_command
{
	char				**command_with_arguments;
	t_list				*redirect_list;
	char				*parse_error;
}						t_command;

typedef struct			s_env
{
	void				*key;
	void				*value;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct			s_data
{
	t_list				*redirect_list;
	t_env				*env_list;
	char				**ar;
	char				*wr_file_name;
	int					wr_type_redir;
	char				*rd_file_name;
	int					redir_flag;
	int					redir_pipe_flag;
	int					fd_start[2];
}						t_data;

void					process_command_envs(
						char **command_with_args, t_data *data);
void					process_redirect_envs(
						t_list *redirect_list, t_data *data);

#endif
