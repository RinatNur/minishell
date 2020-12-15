#ifndef MiNISHELL_H
# define MiNISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include <./libft/libft.h>
#include <dirent.h>
#include "processing.h"
#include "parser.h"

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
	char         **command_with_arguments;
	t_env       *redirect_list;
	t_env       *option_list;
}					t_command;


#endif