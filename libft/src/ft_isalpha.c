/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 13:53:03 by jrocha            #+#    #+#             */
/*   Updated: 2021/12/21 10:41:31 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The ft_isalpha() function checks for an alphabetic character.
// Tt is equivalent to (isupper(c) || islower(c)).
int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
