/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 10:57:11 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/05 14:03:30 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../header/libft.h"

// The ft_strchr() function returns a pointer to the first occurrence of the 
// character c in the string s.
char	*ft_strchr(const char *s, int c)
{
	if (s != NULL)
	{
		while (*s != '\0')
		{
			if (*s == (char)c)
			{
				return ((char *)s);
			}
			s++;
		}
		if (*s == (char)c)
		{
			return ((char *)s);
		}
	}
	return (NULL);
}
