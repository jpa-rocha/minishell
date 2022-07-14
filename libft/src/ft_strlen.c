/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 11:36:39 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/13 10:03:52 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// The ft_strlen() function calculates the length of the string pointed to by s,
// excluding the terminating null byte ('\0').
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

// Returns the strlen of the shortest string given
size_t	ft_short_strlen(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 <= len2)
		return (len1);
	else
		return (len2);
}
