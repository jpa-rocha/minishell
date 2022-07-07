/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:43:45 by jrocha            #+#    #+#             */
/*   Updated: 2021/12/21 11:19:10 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// The  ft_memchr() function scans the initial n bytes of the memory area 
// pointed to by s for the first instance of c.  Both c and the bytes of
// the memory area pointed to by s are interpreted as unsigned char.
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*p;
	unsigned char		*ret;

	ret = NULL;
	p = (unsigned char *)s;
	while (n != 0)
	{
		if (*p != (unsigned char)c)
		{
			p++;
		}
		else
		{
			ret = p;
			return (ret);
		}
		n--;
	}
	return (NULL);
}
