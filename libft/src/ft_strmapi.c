/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 12:50:37 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 13:02:21 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

// The ft_strmapi() function applies the function ’f’ to each character of
// the string ’s’ , and passing its index as first argument to create a new 
// string with ft_calloc() resulting from successive applications of ’f’.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char				*retstr;
	unsigned int		len;
	unsigned int		i;

	if (s != NULL)
	{
		if (f != NULL)
		{
			i = 0;
			len = ft_strlen(s);
			retstr = ft_calloc(len + 1, sizeof(char));
			if (retstr == NULL)
				return (NULL);
			ft_strlcpy(retstr, s, len + 1);
			while (i < len)
			{
				retstr[i] = f(i, retstr[i]);
				i++;
			}
			return (retstr);
		}
		return (NULL);
	}
	return (NULL);
}
