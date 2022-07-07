/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:38:16 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 13:02:57 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/libft.h"

static char			*transcriber(char *string, unsigned int num, int count);
static unsigned int	udigitcount(unsigned int n);

char	*ft_utoa(unsigned int num)
{
	int		count;
	char	*strnbr;

	count = udigitcount(num);
	strnbr = ft_calloc((count) + 1, sizeof(char));
	if (strnbr == NULL)
	{
		return (NULL);
	}
	strnbr = transcriber(strnbr, num, count);
	return (strnbr);
}

static char	*transcriber(char *string, unsigned int num, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		string[i] = (num % 10) + '0';
		num = num / 10;
		i++;
	}
	string[i] = '\0';
	string = ft_revstring(string);
	return (string);
}

static unsigned int	udigitcount(unsigned int n)
{
	unsigned int	count;

	count = 1;
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}
