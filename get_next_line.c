/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrave <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:00:33 by mbrave            #+#    #+#             */
/*   Updated: 2019/03/01 22:48:14 by mbrave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	verify_line(char **str1, char **line1, const int fd1, int bytes_read1)
{
	int		i;
	char	*temp;

	i = 0;
	while (str1[fd1][i] != '\n' && str1[fd1][i] != '\0')
		i++;
	if (str1[fd1][i] == '\n')
	{
		*line1 = ft_strsub(str1[fd1], 0, i);
		temp = ft_strdup(str1[fd1] + i + 1);
		free(str1[fd1]);
		str1[fd1] = temp;
		if (str1[fd1][0] == '\0')
			ft_strdel(&str1[fd1]);
	}
	else if (str1[fd1][i] == '\0')
	{
		if (bytes_read1 == BUFF_SIZE)
			return (get_next_line(fd1, line1));
		*line1 = ft_strdup(str1[fd1]);
		ft_strdel(&str1[fd1]);
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	int			bytes_read;
	char		buff[BUFF_SIZE + 1];
	char		*holder;
	static char	*str[MAX_FD];

	bytes_read = 0;
	if (fd < 0 || line == NULL || fd > MAX_FD)
		return (ERROR);
	if (!str[fd])
		str[fd] = ft_strnew(1);
	while ((bytes_read = read(fd, buff, BUFF_SIZE)))
	{
		if (bytes_read < 0)
			return (ERROR);
		buff[bytes_read] = '\0';
		holder = ft_strjoin(str[fd], buff);
		if (str[fd])
			free(str[fd]);
		str[fd] = holder;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (bytes_read == 0 && (str[fd] == NULL || str[fd][0] == '\0'))
		return (0);
	return (verify_line(str, line, fd, bytes_read));
}
