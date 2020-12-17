#include "processing.h"

ssize_t     ft_write(int fd, const void *buf)
{
    int     len;
    int     ret;
    len = ft_strlen(buf);
    ((ret = write(fd, buf, len)) == -1) ? ft_error("Error in function write", 3) : 0;
    return (ret);
}