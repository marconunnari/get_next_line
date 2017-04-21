/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:51:47 by mnunnari          #+#    #+#             */
/*   Updated: 2017/04/21 17:52:23 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			split(char **line, char *string, char *newlineptr, char **remain)
{
	*line = ft_strjoin(*line, ft_strsub(string, 0, newlineptr - string));
	*remain = newlineptr + 1;
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	char			*buffer;
	char			*newlineptr;
	static char		*remain;
	int				ret;

	*line = "";
	if (remain)
	{
		if ((newlineptr = ft_strchr(remain, '\n')))
			return (split(line, remain, newlineptr, &remain));
		*line = ft_strjoin(*line, remain);
	}
	IFRETURN(!(buffer = ft_strnew(BUFF_SIZE + 1)), -1);
	while ((ret = read(fd, buffer, BUFF_SIZE) > 0))
	{
		if ((newlineptr = ft_strchr(buffer, '\n')))
			return (split(line, buffer, newlineptr, &remain));
		else
			*line = ft_strjoin(*line, buffer);
	}
	IFRETURN(ret == -1, -1);
	return (0);
}
