#include "minishell.h"

void    ft_echo(t_data *data)
{
    int     i;
    int     flag;

    i = (!ft_strncmp(data->ar[1], "-n", (ft_strlen(data->ar[1]) + 1))) ? 2 : 1;
    flag = (i == 1) ? 0 : 1;
    while (data->ar[i])
    {
        ft_write(1, data->ar[i++]);
        if (data->ar[i])
            ft_write(1, " ");
    }
    if (!flag)
        ft_write(1, "\n");
}
