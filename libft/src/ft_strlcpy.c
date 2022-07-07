/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 12:05:53 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 13:02:13 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

// The strlcpy() function copies up to size - 1 characters from 
// the NUL-terminated string src to dst, NUL-terminating the result.
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	ret;

	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			if (i == size - 1)
			{
				break ;
			}
			i++;
		}
		dest[i] = '\0';
	}
	ret = ft_strlen(src);
	return (ret);
}
