/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <wrudy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 14:58:22 by wrudy             #+#    #+#             */
/*   Updated: 2020/12/09 17:50:48 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	ft_countwords(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != c && s[i + 1] == c) ||
			(s[i] != c && s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_len(char const *s, char c)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s[i] == c)
		i++;
	while (s[i] != '\0' && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static void		*arr_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char			**ft_split(char const *s, char c) //TODO В случае ошибки памяти вызывать exit()
{
	char	**arr; //FIXME sdofgkdj
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	if (s == NULL || !(arr = (char**)malloc(sizeof(char*) *
			(ft_countwords(s, c) + 1))))
		return (NULL);
	while (i < ft_countwords(s, c))
	{
		if (!(arr[i] = (char*)malloc(sizeof(char) * (ft_len(s + k, c) + 1))))
			return (arr_free(arr));
		j = 0;
		while (s[k] == c)
			k++;
		while (s[k] != '\0' && s[k] != c)
			arr[i][j++] = s[k++];
		arr[i][j] = '\0';
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
