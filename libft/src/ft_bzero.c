/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:30:18 by jrocha            #+#    #+#             */
/*   Updated: 2021/12/21 10:38:15 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// The ft_bzero() function erases the data in the n bytes of the memory 
// starting at the location pointed to by s, by writing zeros 
// (bytes containing '\0') to that area.
void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*p;

	i = 0;
	p = s;
	while (i < n)
	{
		p[i] = '\0';
		i++;
	}
}
