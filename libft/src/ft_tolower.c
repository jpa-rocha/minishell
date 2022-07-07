/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 10:38:47 by jrocha            #+#    #+#             */
/*   Updated: 2021/12/21 11:06:19 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The ft_tolower() function returns the lowercase equivalent of an uppercase
// char
int	ft_tolower(int c)
{
	if (c >= 0 && c <= 255)
	{
		if (c >= 'A' && c <= 'Z')
		{
			c = c + 32;
		}	
	}
	return (c);
}
