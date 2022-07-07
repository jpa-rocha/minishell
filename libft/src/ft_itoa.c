/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:09:18 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 13:00:04 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static char	*transcriber(char *string, int n, int count, int sign);
static char	*intmin(void);

// The ft_itoa() function turns an integer 
// into a string representation of itself.
char	*ft_itoa(int n)
{
	int		count;
	int		neg;
	char	*strnbr;

	if (n == -2147483648)
	{
		strnbr = intmin();
		return (strnbr);
	}
	if (n < 0)
	{
		n = n * -1;
		neg = 2;
	}
	else
		neg = 1;
	count = digitcount(n);
	strnbr = ft_calloc((count) + neg, sizeof(char));
	if (strnbr == NULL)
	{
		return (NULL);
	}
	strnbr = transcriber(strnbr, n, count, neg);
	return (strnbr);
}

static char	*intmin(void)
{
	char	*intmin;

	intmin = ft_calloc(12, sizeof(char));
	if (intmin == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(intmin, "-2147483648", 12);
	return (intmin);
}

static char	*transcriber(char *string, int n, int count, int sign)
{
	int	i;

	i = 0;
	while (i < count)
	{
		string[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	if (sign == 2)
	{
		string[i] = '-';
		i++;
		string[i] = '\0';
	}
	else
	{
		string[i] = '\0';
	}	
	string = ft_revstring(string);
	return (string);
}
