/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:51:47 by mnunnari          #+#    #+#             */
/*   Updated: 2017/04/23 19:02:19 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				process_line(char **line, char *string,
						char *newlineptr, t_remain *remain)
{
	if ((newlineptr = ft_strchr(string, '\n')))
	{
		*line = ft_strjoin(*line, ft_strsub(string, 0, newlineptr - string));
		remain->content = newlineptr + 1;
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

int				process_fd(t_remain *remain, char **line)
{
	char			*buffer;
	char			*newlineptr;
	int				ret;

	*line = ft_strnew(1);
	newlineptr = NULL;
	if (remain->content)
	{
		IFRETURN(process_line(line, remain->content, newlineptr, remain), 1);
		remain->content = NULL;
	}
	IFRETURN(!(buffer = ft_strnew(BUFF_SIZE + 1)), -1);
	IFRETURN(read(remain->fd, buffer, 0) < 0, -1);
	while ((ret = read(remain->fd, buffer, BUFF_SIZE) > 0))
	{
		IFRETURN(process_line(line, buffer, newlineptr, remain), 1);
		free(buffer);
		IFRETURN(!(buffer = ft_strnew(BUFF_SIZE + 1)), -1);
	}
	IFRETURN(ret == -1, -1);
	IFRETURN(*line && !ft_strequ(*line, ""), 1);
	return (0);
}

t_remain		*find_remain(t_list *remains, int fd)
{
	t_list			*remainsptr;
	t_remain		*remain;

	remain = NULL;
	if (remains)
	{
		remainsptr = remains;
		while (remainsptr && !remain)
		{
			remain = (t_remain*)remainsptr->content;
			if (!(remain->fd == fd))
				remain = NULL;
			remainsptr = remainsptr->next;
		}
	}
	return (remain);
}

t_remain		*create_remain(t_list **remains, int fd)
{
	t_list			*remainsptr;
	t_remain		*remain;

	IFRETURN(!(remain = (t_remain*)malloc(sizeof(t_remain))), NULL);
	remain->fd = fd;
	remain->content = NULL;
	IFRETURN(!(remainsptr = ft_lstnew(remain, sizeof(t_remain))), NULL);
	if (*remains)
		ft_lstadd(remains, remainsptr);
	else
		*remains = remainsptr;
	remain = (t_remain*)(*remains)->content;
	return (remain);
}

int				get_next_line(const int fd, char **line)
{
	static t_list		*remains;
	t_remain			*remain;

	IFRETURN(fd < 0 || !line, -1);
	remain = find_remain(remains, fd);
	if (!remain)
		remain = create_remain(&remains, fd);
	IFRETURN(!remain, -1);
	return (process_fd(remain, line));
}
