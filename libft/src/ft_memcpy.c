/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:29:10 by jrocha            #+#    #+#             */
/*   Updated: 2021/12/21 10:35:09 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// The ft_memcpy() function copies n bytes from memory area src to 
// memory area dest.  The memory areas must not overlap.
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*retdest;
	char	*wsrc;
	size_t	i;

	if (dest == NULL && src == NULL)
	{
		return (0);
	}
	i = 0;
	retdest = (char *) dest;
	wsrc = (char *) src;
	while (i < n)
	{
		retdest[i] = wsrc[i];
		i++;
	}
	return (retdest);
}
