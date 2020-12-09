
#include "utils.h"

char get_flag(unsigned char *flag, char symbol, char control)
{
	if (symbol == control)
	{
		*flag = ~(*flag);
		if (*flag == 1)
			return 0;
	}
	if (*flag == 1)
		return 1;
	else
		return 0;
}

char	*get_mask(char *line)
{
	int				i;
	char			*result;
	unsigned char	flag;
	char 			control_symbol;

	i = 0;
	flag = 1;
	if (!(result = malloc(sizeof(char) * ft_strlen(line))))
		exit(EXIT_FAILURE);
	while (line[i] != '\0')
	{
		if (flag == 1 && (line[i] == '\'' || line[i] == '\"'))
			control_symbol = line[i];
		result[i] = get_flag(&flag, line[i], control_symbol);
		i++;
	}
	return result;
}
