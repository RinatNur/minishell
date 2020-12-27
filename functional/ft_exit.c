#include "processing.h"

void 	ft_exit(t_data *data)
{
//	int 	i;
//	int 	errnum;
//
//	errnum = 0;
//	i = 1;
//	while (data->ar[i])
//		i++;
//	if (i == 2)
//	{
//		errnum = ft_atoi(data->ar[i]);
//	}
//	g_code = -(errnum%256) + 256;
	ft_error("exit", g_code);
}
