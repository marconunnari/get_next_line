/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnunnari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 17:53:00 by mnunnari          #+#    #+#             */
/*   Updated: 2017/04/24 18:47:50 by mnunnari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include "libft.h"

typedef struct		s_remain
{
	int				fd;
	char			*content;
}					t_remain;

int					get_next_line(int fd, char **str);

# define BUFF_SIZE 32

#endif
