/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 09:59:45 by jrocha            #+#    #+#             */
/*   Updated: 2021/12/21 10:42:31 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The ft_isdigit() function checks for a digit (0 through 9).
int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
