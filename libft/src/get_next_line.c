/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:57:34 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/05 14:04:31 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../header/libft.h"

static char	*readjoin(char *buf, char *reader, int rl);
static char	*linecatcher(char **reader);
static char	*newlinegen(char *str, int *i);
static char	*freepointer(char *str, char *ret);

char	*get_next_line(int fd, int term)
{
	static char	*reader;
	char		buf[100 + 1];
	int			readlen;

	if (term == 1)
	{
		return (freepointer(reader, NULL));
	}
	if (fd < 0)
		return (NULL);
	readlen = read(fd, buf, 100);
	if (readlen < 0)
		return (NULL);
	while (readlen > 0)
	{
		buf[readlen] = '\0';
		reader = readjoin(buf, reader, readlen);
		if (ft_strchr(reader, '\n') != NULL)
			break ;
		readlen = read(fd, buf, 100);
	}
	if (readlen == 0 && reader == NULL)
		return (NULL);
	return (linecatcher(&reader));
}

static char	*readjoin(char *buf, char *reader, int rl)
{
	char	*tmp;

	if (buf == NULL)
		return (NULL);
	if (reader == NULL || ft_strlen(reader) == 0)
	{
		tmp = malloc((rl + 1) * sizeof(char));
		if (tmp == NULL)
			return (NULL);
		ft_strlcpy(tmp, buf, rl + 1);
		free(reader);
		return (tmp);
	}
	tmp = reader;
	reader = ft_strjoin(tmp, buf);
	free(tmp);
	return (reader);
}

static char	*freepointer(char *str, char *ret)
{
	if (str != NULL)
		free(str);
	if (ret != NULL)
		free(ret);
	return (NULL);
}

static char	*linecatcher(char **reader)
{
	char	*ret;
	char	*str;
	int		len;

	str = *reader;
	len = 0;
	ret = newlinegen(str, &len);
	if (ret == NULL)
		return (freepointer(str, ret));
	if (ft_strlen(ret) == 0)
		return (freepointer(str, ret));
	*reader = malloc(((ft_strlen(str) - len + 1)) * sizeof(char));
	if (*reader == NULL)
		return (freepointer(str, ret));
	ft_strlcpy(*reader, &str[len], ft_strlen(str) - len + 1);
	free(str);
	return (ret);
}

static char	*newlinegen(char *str, int *i)
{
	char	*dest;

	while (str[*i] != '\n' && str[*i] != '\0' )
		*i = *i + 1;
	if (str[*i] == '\n')
		*i = *i + 1;
	if (ft_strlen(str) == 0)
		return (NULL);
	dest = malloc(((*i) + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, str, *i + 1);
	return (dest);
}
