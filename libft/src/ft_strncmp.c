/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:45:40 by jrocha            #+#    #+#             */
/*   Updated: 2022/08/31 12:18:19 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

// The  ft_strncmp() function compares the two strings s1 and s2. It returns an 
// integer less than, equal to, or greater than zero if s1 is found, 
// respectively, to be less than, to match, or be greater than s2.
// It compares only the first (at most) n bytes of s1 and s2.
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
	{
		return (0);
	}
	while (t1[i] == t2[i] && t1[i] != '\0' && t2[i] != '\0' && i < n - 1)
	{
		i++;
	}
	return (t1[i] - t2[i]);
}
