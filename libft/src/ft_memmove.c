/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:37:05 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 13:00:17 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../header/libft.h"

static void	mover(unsigned char *tdest, unsigned char *tmp, size_t n);

// The ft_memmove() function copies n bytes from memory area src
// to memory area dest. The memory areas may overlap: copying takes place as
// though the bytes in src are first copied into a temporary array that does not
// overlap src or dest, and the bytes are then copied from 
// the temporary array to dest.
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*tdest;

	if (dest == NULL && src == NULL)
		return (0);
	tdest = (unsigned char *) dest;
	tmp = (unsigned char *) src;
	mover(tdest, tmp, n);
	return (dest);
}

static void	mover(unsigned char *tdest, unsigned char *tmp, size_t n)
{
	size_t			i;

	i = 0;
	if (tdest > tmp)
	{
		while (n > 0)
		{
			tdest[n - 1] = tmp[n - 1];
		n--;
		}
	}
	else
	{
		while (i < n)
		{
			tdest[i] = tmp[i];
			i++;
		}
	}
}
