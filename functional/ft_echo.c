/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:06:33 by jheat             #+#    #+#             */
/*   Updated: 2021/01/12 18:06:36 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

static void		print_args(t_data *data, int i)
{
	int		flag;

	flag = (i > 1) ? 1 : 0;
	while (data->ar[i])
	{
		ft_write(1, data->ar[i]);
		if (data->ar[i + 1])
			ft_write(1, " ");
		i++;
	}
	if (!flag)
		ft_write(1, "\n");
}

static int		skip_n_symbols(t_data *data, int i, int *j, int *flag)
{
	while (data->ar[i][*j] != '\0')
	{
		if (data->ar[i][*j] == 'n')
			(*j)++;
		else
		{
			(*flag)++;
			return (1);
		}
	}
	return (0);
}

void			ft_echo(t_data *data)
{
	int		i;
	int		j;
	int		flag;

	i = 1;
	flag = 0;
	while (data->ar[i])
	{
		j = 0;
		if (data->ar[i][j] == '-')
		{
			j++;
			if ((skip_n_symbols(data, i, &j, &flag)) == 1)
				break ;
		}
		if (!flag && j)
			i++;
		else
			break ;
	}
	print_args(data, i);
}
