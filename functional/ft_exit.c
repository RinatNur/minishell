#include "processing.h"

void 	skip_whitespaces(const char *str, int *i, int *sign)
{
	while ((str[(*i)] == 32) || (str[(*i)] > 8 && str[(*i)] < 14))
		i++;
	if ((str[(*i)] == '-' || str[(*i)] == '+') && ft_isdigit(str[(*i) + 1]))
	{
		if (str[(*i)] == '-')
			*sign = -1;
		i++;
	}
}

unsigned long long	ft_atoi_u_long_long(const char *str, int *is_valid, int *is_str)
{
	int		i;
	int		sign;
	unsigned long long res;
	unsigned long long tmp;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i])
	{
		skip_whitespaces(str, &i, &sign);
		if (ft_isdigit(str[i]))
		{
			while (ft_isdigit(str[i]))
			{
				res = res * 10 + str[i++] - '0';
				tmp = res;
				if ((res > 9223372036854775807) && ((tmp * (-1)) != (-9223372036854775807 - 1) || sign > 0))
				{
					*is_valid = 0;
					return (0);
				}
			}
			return (res == 0 ? 0 : (res * sign));
		}
		else
		{
			*is_str = 0;
			return (0);
		}
	}
	return (0);
}

void 	ft_exit(t_data *data)
{
	int 	i;
	int 	errnum;
	unsigned char	*err_u_char;
	unsigned char	err_u;
	int 	is_valid;
	int		is_str;

	is_valid = 1;
	is_str = 1;
	errnum = 0;
	i = 0;
	err_u_char = (unsigned char *)data->ar[1];
	while (data->ar[i + 1])
		i++;
	if (i == 0)
		ft_error("exit", (g_code = 0));
	else if (i == 1)
	{
		err_u = (unsigned char)ft_atoi_u_long_long(data->ar[1], &is_valid, &is_str);
		if (err_u == 0 && (!is_str || !is_valid))
		{
			g_code = 255;
			ft_error_print(MSHELL, data->ar[0], data->ar[1], "numeric argument required");
		}
		else if (err_u > 0 && is_valid)
			g_code = err_u;
//		else if ()

	}
	ft_error("exit", g_code);
}
