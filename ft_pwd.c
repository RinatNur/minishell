#include "minishell.h"

char        *ft_pwd()
{
    char *dir;

    dir = NULL;
    dir = getcwd(dir, 0);
    if (!dir)
        return (NULL);
    return (dir);
//    int i = 0, len, j;

//    while (i < env_len)
//    {
//        if (env[i][0] == 'P' && env[i][1] == 'W' && env[i][2] == 'D')
//        {
//            len = ft_strlen(env[i]) - 4;
//            pwd = (char *)malloc(len + 1);
//            j = 4;
//            while (env[i][j])
//            {
//                pwd[j - 4] = env[i][j];
//                j++;
//            }
//            pwd[j] = '\0';
//            break ;
//        }
//        i++;
//    }
}
