#ifndef MINISHELL_PARSE_H
#define MINISHELL_PARSE_H
#include "utils/utils.h"


/*
** list of words
*/
typedef struct		s_word
{
	char			*word;
	int 			len;
	void			(* destroy)(struct s_word *self);
}					t_word;

t_word				*word_constructor(char *word);
void 				word_destructor(t_word *self);

#endif //MINISHELL_PARSE_H