/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrudy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:39:36 by wrudy             #+#    #+#             */
/*   Updated: 2021/01/14 17:39:38 by wrudy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	set_mask_symbol(int *flag, char *env_mask, const char *arg, int *i)
{
	*flag = 1;
	env_mask[(*i)] = '$';
	if (arg[(*i) + 1] == '$')
	{
		*flag = 0;
		env_mask[(*i) + 1] = '!';
		(*i) = (*i) + 2;
		return ;
	}
	if (arg[(*i) + 1] == '?')
	{
		*flag = 0;
		env_mask[(*i) + 1] = '?';
		(*i) = (*i) + 2;
		return ;
	}
	(*i)++;
}

char	*env_mask(char *arg)
{
	char	*env_mask;
	char	*quote_mask;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	env_mask = empty_str(' ', u_strlen(arg));
	quote_mask = get_mask(arg);
	while (arg[i] != '\0')
	{
		if (arg[i] == '$' && (quote_mask[i] == '0' || quote_mask[i] == '\"'))
		{
			set_mask_symbol(&flag, env_mask, arg, &i);
			continue ;
		}
		if (flag == 1 && (arg[i] == ' ' ||
		arg[i] == '\"' || arg[i] == '\'' || arg[i] == '='))
			flag = 0;
		if (flag == 1)
			env_mask[i] = 'e';
		i++;
	}
	free(quote_mask);
	return (env_mask);
}

int		mask_elem_len(const char *mask)
{
	int i;

	if (mask[0] == '$')
	{
		i = 1;
		if (mask[i] == '!' || mask[i] == '?')
			return (2);
		while (mask[i] != '\0' && mask[i] != ' ' && mask[i] != '$')
			i++;
	}
	else
	{
		i = 0;
		while (mask[i] != '\0' && mask[i] != '$')
			i++;
	}
	return (i);
}

int		env_count(const char *arg, const char *mask)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (arg[i] != '\0')
	{
		if (mask[i] == '$')
			count++;
		i++;
	}
	i = 0;
	while (arg[i] != '\0')
	{
		if (mask[i] == ' ' && (mask[i + 1] == '$' || mask[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

char	**parse_env(char *arg)
{
	char	*mask;
	int		i;
	int		j;
	char	**result;

	mask = env_mask(arg);
	j = env_count(arg, mask);
	if (!(result = malloc(sizeof(char *) * (j + 1))))
		exit(0);
	i = 0;
	j = 0;
	while (arg[i] != '\0')
	{
		mask_elem_len(mask + i);
		result[j] = u_strldup(arg + i, mask_elem_len(mask + i));
		j++;
		i = i + mask_elem_len(mask + i);
	}
	free(mask);
	result[j] = NULL;
	return (result);
}
