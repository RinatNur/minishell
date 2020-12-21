
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
		return '0';
	else
		return quote;
}

static char *correct_mask(char *mask)
{
	int i;
	char *result;

	result = u_strdup(mask);
	if (mask[0] == '\'' || mask[0] == '\"')
		result[0] = '0';
	i = 1;
	while (mask[i] != 0)
	{
		if ((mask[i - 1] == '0' || (mask[i + 1] == '0' || mask[i + 1] == '\0'))
			&& (mask[i] == '\'' || mask[i] == '\"'))
			result[i] = '0';
		i++;
	}
	free(mask);
	return (result);
}

char	*get_mask(char *line)
{
	int				i;
	char			*result;
	unsigned char	flag;
	char 			quote;

	if (!(result = malloc(sizeof(char) * u_strlen(line) + 1)))
		exit(EXIT_FAILURE);
	i = 0;
	flag = 1;
	quote = '\0';
	while (line[i] != '\0')
	{
		if (flag == 1 && (line[i] == '\'' || line[i] == '\"'))
			quote = line[i];
		result[i] = mask_elem(&flag, line[i], quote);
		i++;
	}
	result[i] = 0;
	result = correct_mask(result);
	return result;
}
