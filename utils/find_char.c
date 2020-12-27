//
// Created by Wolmer Rudy on 12/27/20.
//

#include "utils.h"

int find_char(const char *str, char c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			break;
		i++;
	}
	if (str[i] == '\0')
		return -1;
	else
		return i;
}