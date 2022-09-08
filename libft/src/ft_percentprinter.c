/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percentprinter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:50:38 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/07 10:05:40 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

int	percentprinter(int fd, char *flags)
{
	int	i;

	i = 0;
	while (flags[i] == '%')
		i++;
	i = i / 2;
	while (i != 0)
	{
		ft_putchar_fd('%', fd);
		i--;
	}
	return (ft_strlen(flags) / 2);
}
