/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:26:55 by jrocha            #+#    #+#             */
/*   Updated: 2022/05/05 11:31:30 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_power(int base, int exp)
{
	int	result;

	result = 1;
	while (exp)
	{
		result = result * base;
		exp--;
	}
	return (result);
}
