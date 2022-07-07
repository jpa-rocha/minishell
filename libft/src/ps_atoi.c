/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 10:14:57 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 13:04:18 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#include <stdlib.h>

static long long	intinit(const char *nptr);
static char			*truncator(char *nptr);

// The ps_atoi() function converts the initial portion of 
// the string pointed to by nptr to int (extra for push_swap).
long long	ps_atoi(const char *nptr)
{
	char			*ptr;
	long long		res;
	int				sign;

	res = 0;
	sign = 0;
	ptr = (char *) nptr;
	if (ft_isplusminus(ptr[0]) != 0 && ft_isdigit(ptr[1]) == 1)
	{
		sign = ft_isplusminus(ptr[0]);
		ptr = truncator(ptr);
	}
	if (ft_isdigit(ptr[0]) == 1)
	{
		res = intinit(ptr);
		if (sign == 2)
			res = res * -1;
		return (res);
	}
	return (0);
}

static long long	intinit(const char *nptr)
{
	long long	i;
	long long	res;

	res = 0;
	i = 0;
	while (ft_isdigit(nptr[i]) == 1)
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res);
}

static char	*truncator(char *nptr)
{
	char	*ptr;

	ptr = NULL;
	if (ft_isplusminus(nptr[0]) != 0)
	{
		ptr = &nptr[1];
	}
	return (ptr);
}
