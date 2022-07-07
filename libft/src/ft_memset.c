/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 09:47:49 by jrocha            #+#    #+#             */
/*   Updated: 2022/02/20 17:41:03 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// The ft_memset() function fills the first n bytes of the memory area pointed 
// to by s with the constant byte c.
void	*ft_memset(void *s, int c, size_t n)
{
	size_t		i;
	char		*p;

	i = 0;
	p = s;
	while (i < n)
	{
		p[i] = c;
		i++;
	}
	return (s);
}
