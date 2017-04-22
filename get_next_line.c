/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:51:47 by mnunnari          #+#    #+#             */
/*   Updated: 2017/04/22 18:22:33 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				process_line(char **line, char *string,
						char *newlineptr, char **remain)
{
	if ((newlineptr = ft_strchr(string, '\n')))
	{
		*line = ft_strjoin(*line, ft_strsub(string, 0, newlineptr - string));
		*remain = newlineptr + 1;
		return (1);
	}
	else
	{
		if (*line)
			*line = ft_strjoin(*line, string);
		else
			*line = string;
		return (0);
	}
}

int				process_fd(const int fd, char **line, char **remain)
{
	char			*buffer;
	char			*newlineptr;
	int				ret;

	*line = "";
	newlineptr = NULL;
	if (*remain)
	{
		IFRETURN(process_line(line, *remain, newlineptr, remain), 1);
		*remain = NULL;
	}
	IFRETURN(!(buffer = ft_strnew(BUFF_SIZE + 1)), -1);
	while ((ret = read(fd, buffer, BUFF_SIZE) > 0))
	{
		IFRETURN(process_line(line, buffer, newlineptr, remain), 1);
		IFRETURN(!(buffer = ft_strnew(BUFF_SIZE + 1)), -1);
	}
	IFRETURN(ret == -1, -1);
	IFRETURN(*line && !ft_strequ(*line, ""), 1);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		**remains;
	char			**remain;

	IFRETURN(fd < 0, -1);
	if (!remains)
		remains = (char**)malloc(sizeof(char*) * 1024);
	IFRETURN(!remains, -1);
	remain = &remains[fd];
	return (process_fd(fd, line, remain));
}
