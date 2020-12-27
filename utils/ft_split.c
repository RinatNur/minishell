/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 14:58:22 by wrudy             #+#    #+#             */
/*   Updated: 2020/12/12 19:08:14 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	ft_countwords(char const *s, char c, const char *mask)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c && (s[i + 1] == c && mask[i + 1] == '0')) ||
			(s[i] != c && s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_len(char const *s, char c, const char *mask)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s[i] == c && mask[i] == '0')
		i++;
	while (s[i] != '\0' && !(s[i] == c && mask[i] == '0'))
	{
		len++;
		i++;
	}
	return (len);
}

void 			free_2d_array(void **array)
{
	int i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char			**u_split(char const *s, char c, const char *mask)
{
	char	**arr;
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	if (s == NULL)
		return (0);
	if (!(arr = (char**)malloc(sizeof(char*) * (ft_countwords(s, c, mask) + 1))))
		exit(EXIT_FAILURE);
	while (i < ft_countwords(s, c, mask))
	{
		if (!(arr[i] = (char*)malloc(sizeof(char) * (ft_len(s + k, c, mask + k) + 1))))
			exit(EXIT_FAILURE);
		j = 0;
		while (s[k] == c && mask[k] == '0')
			k++;
		while (s[k] != '\0' && !(s[k] == c && mask[k] == '0'))
			arr[i][j++] = s[k++];
		arr[i][j] = '\0';
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
