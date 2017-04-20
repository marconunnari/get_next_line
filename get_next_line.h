#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"

int		get_next_line(int fd, char **str);

#define BUFF_SIZE 32

#endif
