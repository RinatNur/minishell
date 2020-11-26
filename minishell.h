#ifndef MiNISHELL_H
# define MiNISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <./libft/libft.h>


char        *ft_pwd();
size_t      ft_strlen(const char *s);
void        ft_env(char **env, int env_len);

#endif