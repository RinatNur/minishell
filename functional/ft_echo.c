/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 14:18:47 by jheat             #+#    #+#             */
/*   Updated: 2021/01/14 14:18:49 by jheat            ###   ########.fr       */
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

static void		init(int *i, int *flag)
{
	*i = 1;
	*flag = 0;
}

void			ft_echo(t_data *data)
{
	int		flag;
	int		i;
	int		j;

	init(&i, &flag);
	while (data->ar[i])
	{
		j = 0;
		if (data->ar[i][j] == '-')
		{
			j++;
			while (data->ar[i][j] != '\0')
			{
				if (data->ar[i][j] == 'n')
					j++;
				else if ((++flag))
					break ;
			}
		}
		if (!flag && j)
			i++;
		else
			break ;
	}
	print_args(data, i);
}
