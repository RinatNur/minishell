#include "processing.h"

void    ft_echo(t_data *data)
{
    int     i, j;
    int     flag;

    i = 1;
//    i = (!ft_strncmp(data->ar[1], "-n", (ft_strlen(data->ar[1]) + 1))) ? 2 : 1;
//    flag = (i == 1) ? 0 : 1;
    while (data->ar[i])
    {
		j = 0;
		if (data->ar[i][j] == '-')
		{
			j++;
			flag = 0;
			while (data->ar[i][j] != '\0')
			{
				if (data->ar[i][j] == 'n')
					j++;
				else
				{
					flag++;
					break;
				}
			}
		}
		if (!flag && j)
			i++;
		else
			break;
	}
	flag = (i > 1) ? 1 : 0;
    while (data->ar[i])
	{
       	ft_write(1, data->ar[i]);
        if (data->ar[i])
            ft_write(1, " ");
        i++;
	}
    if (!flag)
        ft_write(1, "\n");
}
