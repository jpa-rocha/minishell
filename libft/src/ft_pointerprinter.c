/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointerprinter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:49:56 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 13:00:36 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/libft.h"

int	pointerprinter(unsigned long ptr)
{
	char	*ptrstr;
	char	*start;
	int		len;

	start = "0x";
	ft_putstr_fd(start, 1);
	if (ptr == 0)
	{
		ft_putchar_fd('0', 1);
		return (ft_strlen(start) + 1);
	}
	ptrstr = ft_convert2hexa(ptr);
	ft_putstr_fd(ptrstr, 1);
	len = ft_strlen(start) + ft_strlen(ptrstr);
	free(ptrstr);
	return (len);
}
