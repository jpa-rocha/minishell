/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:05:12 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/13 09:57:07 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/libft.h"

static int	strstart(char *str, char *set);
static int	strend(char *str, char *set);
static char	*returner(int start, int strsize, const char *s1);
static char	*safetycheck(const char *s1, char *set, int ssize, int srt);

// The ft_strtrim() function allocates (with malloc(3)) and returns a copy of
// ’s1’ with the characters specified in ’set’ removed from the beginning 
// and the end of the string.
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		start;
	int		end;
	int		strsize;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (NULL);
	start = strstart((char *) s1, (char *) set);
	end = strend((char *) s1, (char *) set);
	strsize = ft_strlen((char *) s1) - end;
	end = strsize - start;
	if (end < 0 || ft_strlen((char *)set) == 0 || ft_strlen(s1) == 0)
	{
		ret = safetycheck(s1, (char *) set, strsize, start);
		return (ret);
	}
	ret = returner(start, strsize, s1);
	return (ret);
}

static char	*safetycheck(const char *s1, char *set, int ssize, int srt)
{
	char	*ret;

	if (ft_strlen(s1) == 0 || ssize - srt < 0)
	{
		ret = ft_calloc(1, sizeof(char));
		if (ret == NULL)
		{
			return (NULL);
		}
		return (ret);
	}
	if (ft_strlen(set) == 0)
	{
		ret = ft_calloc(ft_strlen(s1) + 1, sizeof(char));
		if (ret == NULL)
		{
			return (NULL);
		}
		ft_strlcpy(ret, s1, ft_strlen(s1) + 1);
		return (ret);
	}
	return (NULL);
}

static char	*returner(int start, int strsize, const char *s1)
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_calloc((strsize - start) + 1, sizeof(char));
	if (ret == NULL)
	{
		return (NULL);
	}
	while (start < strsize)
	{
		ret[i] = s1[start];
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}

static int	strstart(char *str, char *set)
{
	int	c;
	int	j;
	int	check;

	j = 0;
	c = 0;
	check = ft_strlen(set);
	if (ft_strlen(set) == 0)
		check = 1;
	if (ft_strncmp(set, "", check) != 0)
	{
		while (set[j] != '\0')
		{
			if (str[c] != set[j])
			{
				j++;
			}
			else if (str[c] == set[j])
			{
				c++;
				j = 0;
			}
		}
	}
	return (c);
}

static int	strend(char *str, char *set)
{
	int	c;
	int	j;
	int	len;

	j = 0;
	c = 0;
	len = ft_strlen(str);
	if (len > 0)
		len--;
	while (set[j] != '\0' && len > 0)
	{
		if (str[len] != set[j])
		{
			j++;
		}
		else if (str[len] == set[j])
		{
			c++;
			len--;
			j = 0;
		}
	}
	return (c);
}
