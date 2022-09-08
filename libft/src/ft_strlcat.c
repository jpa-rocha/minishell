/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:38:25 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/08 13:54:46 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../header/libft.h"

// The strlcat() function appends the NUL-terminated string src to the 
// end of dst. It will append at most size - ft_strlen(dst) - 1 bytes, NUL-
// terminating the result.
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	destindex;
	size_t	srcindex;

	i = ft_strlen(dest) + ft_strlen(src);
	destindex = ft_strlen(dest);
	srcindex = 0;
	if (size > 0 && size > ft_strlen(dest))
	{
		while (src[srcindex] != '\0')
		{
			dest[destindex] = src[srcindex];
			if (destindex == size - 1)
			{
				break ;
			}
			destindex++;
			srcindex++;
		}
		dest[destindex] = '\0';
	}
	else
		return (ft_strlen(src) + size);
	return (i);
}
