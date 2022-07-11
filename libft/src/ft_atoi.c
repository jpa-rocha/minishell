/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:38:29 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/11 11:23:47 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static long long	intinit(const char *nptr);
static char			*truncator(char *nptr);

int	ft_atoi(const char *nptr)
{
	char			*ptr;
	int				sign;
	long long		res;

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
	}
	if (res > INT_MAX || res < 0)
		return (-1);
	return (res);
}

static long long	intinit(const char *nptr)
{
	int			i;
	long long	res;

	res = 0;
	i = 0;
	while (ft_isdigit(nptr[i]) == 1)
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	if (ft_isdigit(nptr[i]) != 1 && nptr[i] != '\0')
		res = -1;
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
