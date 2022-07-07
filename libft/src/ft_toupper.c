/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:13:31 by jrocha            #+#    #+#             */
/*   Updated: 2021/12/21 11:07:03 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The ft_toupper() function returns the uppercase equivalent of a lowercase
// char
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c -32);
	}
	return (c);
}
