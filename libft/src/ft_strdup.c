/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:51:12 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 13:01:39 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/libft.h"

// The  strdup() function returns a pointer to a new string which is a 
// duplicate of the string s.  Memory for the new string is 
// obtained with ft_calloc(), and can be freed with free().
char	*ft_strdup(const char *s)
{
	char	*ret;

	ret = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (ret == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(ret, s, ft_strlen(s) + 1);
	return (ret);
}
