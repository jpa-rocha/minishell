/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:28:51 by jrocha            #+#    #+#             */
/*   Updated: 2021/12/21 10:42:18 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The ft_isascii() function checks whether c is a 7-bit unsigned char 
// value that fits into the ASCII character set.
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
