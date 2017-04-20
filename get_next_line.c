#include "get_next_line.h"

int			get_next_line(const int fd, char **line)
{
	(void)fd;
	(void)line;
	char		*buffer;

	IFRETURN(!(buffer = ft_strnew(BUFF_SIZE + 1)), -1);
	return (0);
}
