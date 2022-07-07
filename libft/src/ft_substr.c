/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 10:33:33 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 13:02:41 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/libft.h"

// The ft_substr() function allocates (with malloc(3)) and returns a 
// substring from the string ’s’. The substring begins at index ’start’ 
// and is of maximum size ’len’.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;

	if (s != NULL)
	{
		if (start >= ft_strlen(s))
		{
			ret = ft_calloc(1, sizeof(char));
			if (ret == NULL)
				return (NULL);
			return (ret);
		}
		if (len > ft_strlen(s + start))
			len = ft_strlen(s + start);
		ret = ft_calloc(len + 1, sizeof(char));
		if (ret == NULL)
			return (NULL);
		ft_strlcpy(ret, &s[start], len + 1);
		return (ret);
	}
	return (NULL);
}
