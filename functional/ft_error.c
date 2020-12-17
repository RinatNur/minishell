#include "processing.h"

void    ft_error(char *str, int code)
{
    write (1, str, ft_strlen((str)));
    exit (code);
}
