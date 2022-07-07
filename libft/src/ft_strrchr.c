/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:39:50 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 13:02:32 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../header/libft.h"

// The strrchr() function returns a pointer to the last occurrence of the 
// character c in the string s.
char	*ft_strrchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (*s != '\0')
	{
		s++;
		i++;
	}
	if (c == '\0')
	{
		return ((char *) s);
	}
	while (i >= 0)
	{
		if (*s == (char)c)
		{
			return ((char *) s);
		}
		s--;
		i--;
	}
	return (NULL);
}
