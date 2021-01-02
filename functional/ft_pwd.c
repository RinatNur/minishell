#include "processing.h"

void        *ft_pwd()
{
    char *dir;

    dir = NULL;
    dir = getcwd(dir, 0);
    if (!dir)
	{
    	g_code = errno;
        ft_error_print(MSHELL, "pwd", NULL, strerror(errno));
	}
    ft_write(1, dir);
    write(1, "\n", 1);
}
