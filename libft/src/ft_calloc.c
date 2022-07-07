/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 10:32:21 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 12:59:21 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/libft.h"

// The ft_calloc() function allocates memory for an array of nmemb elements
// of size bytes each and returns a pointer to  the  allocated  memory.
// The memory is set to zero.  If nmemb or size is 0, then calloc() 
// returns either NULL, or a unique pointer value that can later be 
// successfully passed to free().
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc(nmemb * size);
	if (p == NULL)
	{
		return (NULL);
	}
	p = ft_memset(p, 0, nmemb * size);
	return (p);
}
