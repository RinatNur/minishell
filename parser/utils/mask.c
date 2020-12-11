
#include "utils.h"

char mask_elem(unsigned char *flag, char symbol, char quote)
{
	if (symbol == quote)
	{
		*flag = ~(*flag);
		if (*flag == 1)
			return quote;
	}
	if (*flag == 1)
		return 0;
	else
		return quote;
}

char	*get_mask(char *line)
{
	int				i;
	char			*result;
	unsigned char	flag;
	char 			quote;

	i = 0;
	flag = 1;
	if (!(result = malloc(sizeof(char) * ft_strlen(line))))
		exit(EXIT_FAILURE);
	while (line[i] != '\0')
	{
		if (flag == 1 && (line[i] == '\'' || line[i] == '\"'))
			quote = line[i];
		result[i] = mask_elem(&flag, line[i], quote);
		i++;
	}
	return result;
}
