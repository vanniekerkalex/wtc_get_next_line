/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-ni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:09:08 by avan-ni           #+#    #+#             */
/*   Updated: 2018/06/20 17:28:54 by avan-ni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_read_line(char *buf, const int fd, char *left[fd])
{
	int		size;
	char	*temp;

	while ((ft_delchr(buf, '\n') < 0) &&
			((size = read(fd, buf, BUFF_SIZE)) > 0))
	{
		buf[size] = '\0';
		temp = left[fd];
		left[fd] = ft_strjoin(temp, buf);
		ft_strdel(&temp);
	}
	ft_strdel(&buf);
	if (size == -1)
		return (-1);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	char		*buf;
	static char	*left[2147483647];
	int			ret;
	char		*temp;

	buf = ft_strnew(BUFF_SIZE);
	if (fd < 0 || line == NULL || buf == NULL || BUFF_SIZE < 1)
		return (-1);
	if (left[fd] == NULL)
		left[fd] = ft_strnew(0);
	if ((ret = ft_read_line(buf, fd, left)) == -1)
		return (-1);
	if (ft_delchr(left[fd], '\n') >= 0)
	{
		temp = left[fd];
		*line = ft_strnew_del(temp, '\n');
		left[fd] = ft_strnew_delaft(temp, '\n');
		ft_strdel(&temp);
		return (1);
	}
	*line = ft_strdup(left[fd]);
	ft_strdel(&left[fd]);
	return (ft_strlen(*line) > 0 ? 1 : 0);
}
