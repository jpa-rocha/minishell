/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convertfromhexa.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:18:57 by jrocha            #+#    #+#             */
/*   Updated: 2022/05/05 11:37:54 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../header/libft.h"

static int	lower_case_check(char c);
static char	*x_check(char *hexa);

// The convertfromhexa() function converts a given string represented Hexa 
// into its corresponding int variant.
int	ft_convertfromhexa(char *hexa)
{
	int				i;
	int				val;
	int				tmp;
	int				idx;
	char			*hex;

	idx = 1;
	i = 0;
	val = 0;
	hex = x_check(hexa);
	while (hex[i] != '\0')
	{
		if (ft_isdigit(hex[i]) == 1)
			tmp = hex[i] - '0';
		else
			tmp = lower_case_check(hex[i]);
		tmp = tmp * ft_power(16, ft_strlen(hex) - idx);
		val = val + tmp;
		i++;
		idx++;
	}
	return (val);
}

static char	*x_check(char *hexa)
{
	char	*hex;

	hex = ft_strchr(hexa, 'x');
	if (hex != NULL)
		hex++;
	else
		hex = hexa;
	return (hex);
}

static int	lower_case_check(char c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c - 87);
	}
	return (c - 55);
}
