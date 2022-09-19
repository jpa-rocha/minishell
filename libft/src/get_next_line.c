/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:57:34 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/18 21:19:06 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../header/libft.h"

static char	*readjoin(char *buf, char *reader);

char	*get_next_line(int fd)
{
	char		*reader;
	char		buf[1000 + 1];
	int			readlen;

	if (fd < 0)
		return (NULL);
	readlen = read(fd, buf, 100);
	if (readlen <= 0)
		return (NULL);
	reader = ft_calloc(1, sizeof(char));
	ft_memset(reader, 0, 1);
	while (readlen > 0)
	{
		buf[readlen] = '\0';
		reader = readjoin(buf, reader);
		if (ft_strchr(reader, '\n') != NULL)
			break ;
		readlen = read(fd, buf, 100);
	}
	if (readlen == 0 && reader == NULL)
		return (NULL);
	return (reader);
}

static char	*readjoin(char *buf, char *reader)
{
	char	*tmp;

	if (buf == NULL)
		return (NULL);
	if (reader == NULL || ft_strlen(reader) == 0)
	{
		tmp = ft_strdup(buf);
		if (tmp == NULL)
			return (NULL);
		free(reader);
		return (tmp);
	}
	tmp = reader;
	reader = ft_strjoin(tmp, buf);
	free(tmp);
	return (reader);
}
