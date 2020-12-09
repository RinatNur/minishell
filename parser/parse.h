#ifndef MINISHELL_PARSE_H
#define MINISHELL_PARSE_H
#include "utils/utils.h"
#include "stdio.h"


/*
** list of words
*/
typedef struct		s_word
{
	char			*word;
	int 			len;
}					t_word;
t_word				*word_constructor(char *word);
void 				word_destructor(t_word *word);

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
	char			**arguments;
	t_flag			flag;
	t_list			*redirect_list;
}					t_command;

t_list				*parse(char *command_line);
t_command			*parse_command(char *command_str);

#endif //MINISHELL_PARSE_H
