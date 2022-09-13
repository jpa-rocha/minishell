/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:10:22 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/08 14:03:06 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/libft.h"

// The ft_strjoin() allocates with ft_calloc())and returns a new
// string, which is the result of the concatenation of ’s1’ and ’s2’. 
char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*ret;
	size_t		dst;

	if (s1 != NULL && s2 != NULL)
	{
		dst = ft_strlen(s1) + ft_strlen(s2) + 1;
		ret = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
		if (ret == NULL)
		{
			return (NULL);
		}
		ft_strlcpy(ret, s1, dst);
		ft_strlcat(ret, s2, dst);
		return (ret);
	}
	return (NULL);
}
