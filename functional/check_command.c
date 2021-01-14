/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jheat <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 13:51:34 by jheat             #+#    #+#             */
/*   Updated: 2021/01/14 13:51:36 by jheat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "processing.h"

void		check_command(t_data *data)
{
	static int		count = 0;
	char			*com;

	g_code = 0;
	count++;
	com = data->ar[0];
	if (!com)
		return ;
	if (!ft_strncmp("pwd", com, 4) || !ft_strncmp("PWD", com, 4))
		ft_pwd();
	else if (!ft_strncmp("echo", com, 5) || !ft_strncmp("ECHO", com, 5))
		ft_echo(data);
	else if (!ft_strncmp("cd", com, 3) || !ft_strncmp("CD", com, 3))
		ft_cd(data);
	else if (!ft_strncmp("export", com, 7))
		ft_export(data);
	else if (!ft_strncmp("unset", com, 6))
		ft_unset(data);
	else if (!ft_strncmp("env", com, 4))
		ft_env(data);
	else if (!ft_strncmp("exit", com, 5))
		ft_exit(data);
	else
		ft_exec(data);
}
