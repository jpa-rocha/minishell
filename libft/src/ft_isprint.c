/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:35:33 by jrocha            #+#    #+#             */
/*   Updated: 2021/12/21 10:42:50 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The ft_isprint() function checks for any printable character including space.
int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
