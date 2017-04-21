#include "get_next_line.h"

int			get_next_line(const int fd, char **line)
{
	char			*buffer;
	char			*newlineptr;
	static char		*remain;
	int			ret;

	*line = "";
	if (remain)
	{
		if ((newlineptr = ft_strchr(remain, '\n')))
		{
			*line = ft_strjoin(*line, ft_strsub(remain, 0, newlineptr - remain));
			remain = newlineptr + 1;
			return (1);
		}
		*line = ft_strjoin(*line, remain);
	}
	IFRETURN(!(buffer = ft_strnew(BUFF_SIZE + 1)), -1);
	while ((ret = read(fd, buffer, BUFF_SIZE) > 0))
	{
		if ((newlineptr = ft_strchr(buffer, '\n')))
		{
			*line = ft_strjoin(*line, ft_strsub(buffer, 0, newlineptr - buffer));
			remain = newlineptr + 1;
			return (1);
		}
		else
		{
			*line = ft_strjoin(*line, buffer);
		}
	}
	IFRETURN(ret == -1, -1);
	return(0);
}
