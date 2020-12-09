#include "parse.h"

t_word				*word_constructor(char *word)
{
	t_word *result;

	if (!(result = malloc(sizeof(t_word))))
		exit(EXIT_FAILURE);
	result->word = ft_strdup(word);
	result->len = ft_strlen(result->word);
	return (result);
}

void 				word_destructor(t_word *word)
{
	if (word == NULL)
		return ;
	free(word->word);
	free(word);
}