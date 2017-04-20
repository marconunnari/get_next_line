#include "get_next_line.h"

int			get_next_line(const int fd, char **line)
{
	int bytesread = read(fd, *line, BUFF_SIZE);
	bytesread = read(fd, *line, BUFF_SIZE);
	return (bytesread);
}
