#include "minishell.h"

void        *ft_pwd()
{
    char *dir;

    dir = NULL;
    dir = getcwd(dir, 0);
    if (!dir)
        ft_error("pwd is not found", 4);
    ft_write(1, dir);
    write(1, "\n", 1);
}
