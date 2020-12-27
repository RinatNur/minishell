#include "processing.h"

void    ft_echo(t_data *data)
{
    int     i;
    int     flag;

    i = (!ft_strncmp(data->ar[1], "-n", (ft_strlen(data->ar[1]) + 1))) ? 2 : 1;
    flag = (i == 1) ? 0 : 1;
    while (data->ar[i])
    {
    	if ((ft_strncmp("$?", data->ar[i], 3)))//TODO убрать 3 строки если в парсере будет подставляться
        	ft_write(1, data->ar[i]);
        else//TODO
    		ft_write(1, ft_itoa(g_err));//TODO
        i++;
        if (data->ar[i])
            ft_write(1, " ");
    }
    if (!flag)
        ft_write(1, "\n");
}
