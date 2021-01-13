#include "processing.h"

void    ft_echo(t_data *data)
{
    int     i;
    int 	j;
    int     flag;

    i = 1;
    flag = 0;
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
        if (data->ar[i + 1])
            ft_write(1, " ");
        i++;
	}
    if (!flag)
        ft_write(1, "\n");
}
