/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:25:06 by jrocha            #+#    #+#             */
/*   Updated: 2022/05/16 14:35:21 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/libft.h"

static int	wcounter(char const *s, char c);
static char	**allocator(char **list, const char*s, char c);
static char	*suballocator(char *entry, const char *s, int idx, int len);

// The ft_split() function devides a given string into list entries using
// a given char as separator.
char	**ft_split(char const *s, char c)
{
	char	**list;
	char	*workstr;
	int		words;
	char	sep[2];

	sep[0] = c;
	sep[1] = '\0';
	if (s != NULL)
	{
		workstr = ft_strtrim(s, sep);
		if (workstr == NULL)
			return (NULL);
		words = wcounter(workstr, c) + 1;
		list = ft_calloc(words + 1, sizeof(char *));
		if (list == NULL)
			return (NULL);
		list = allocator(list, workstr, c);
		free(workstr);
		return (list);
	}
	return (NULL);
}

static char	**allocator(char **list, const char*s, char c)
{
	int	len;
	int	idx;
	int	lidx;

	len = 0;
	idx = 0;
	lidx = 0;
	while (s[idx] != '\0')
	{
		while (s[idx] == c)
			idx++;
		while (s[idx] != c && s[idx] != '\0')
		{
			len++;
			idx++;
		}
		list[lidx] = suballocator(list[lidx], s, idx, len);
		lidx++;
		len = 0;
	}
	free(list[lidx]);
	return (list);
}

static char	*suballocator(char *entry, const char *s, int idx, int len)
{
	entry = ft_calloc(len + 1, sizeof(char));
	if (entry == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(entry, &s[idx] - len, len + 1);
	return (entry);
}

static int	wcounter(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	if (ft_strncmp(s, "", 1) == 0)
	{
		return (cnt - 1);
	}
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			cnt++;
			while (s[i] == c)
			{
				i++;
			}
		}
		i++;
	}
	return (cnt);
}
