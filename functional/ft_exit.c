/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 19:36:16 by jheat             #+#    #+#             */
/*   Updated: 2021/01/12 19:36:19 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

static int				from_char_to_int(const char *str, int *i,
								int *is_valid, int sign)
{
	unsigned long long res;
	unsigned long long tmp;

	res = 0;
	while (ft_isdigit(str[*i]))
	{
		res = res * 10 + str[*i] - '0';
		tmp = res;
		if ((res > 9223372036854775807) && ((tmp * (-1))
			!= (unsigned long long)(-9223372036854775807 - 1) || sign > 0))
		{
			*is_valid = 0;
			return (0);
		}
		(*i)++;
	}
	if (*i == (int)ft_strlen(str))
		return (res == 0 ? 0 : (res * sign));
	else
	{
		*is_valid = 0;
		return (0);
	}
}

unsigned long long		ft_atoi_u_long_long(const char *str,
										int *is_valid, int *is_str)
{
	int		i;
	int		sign;

	i = 0;
	sign = (str[i] == '-') ? -1 : 1;
	(str[i] == '-' || str[i] == '+') ? i++ : 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (from_char_to_int(str, &i, is_valid, sign));
		else
		{
			*is_str = 1;
			return (0);
		}
	}
	return (0);
}

void					exit_with_dif_code(t_data *data, unsigned char code,
							char *str, ssize_t is_exit)
{
	ft_error("exit", g_code);
	(str) ? ft_error_print(MSHELL, data->ar[0], data->ar[1], str) : 0;
	g_code = code;
	(is_exit) ? exit(g_code) : 0;
}

void					ft_exit(t_data *data)
{
	unsigned char		err_u;
	int					i;
	int					is_valid;
	int					is_str;

	is_valid = 1;
	is_str = 0;
	i = 0;
	while (data->ar[i + 1])
		i++;
	if (i == 0)
		exit_with_dif_code(data, 0, NULL, 1);
	err_u = (unsigned char)ft_atoi_u_long_long(data->ar[1], &is_valid, &is_str);
	if (err_u == 0 && (is_str || !is_valid))
		exit_with_dif_code(data, 255, "numeric argument required", 1);
	if (err_u == 0 && (!is_str || is_valid))
		exit_with_dif_code(data, 0, NULL, 1);
	if (i > 1)
	{
		exit_with_dif_code(data, 1, NULL, 0);
		ft_error_print(MSHELL, data->ar[0], NULL, ERR6);
		return ;
	}
	exit_with_dif_code(data, err_u, NULL, 1);
}
