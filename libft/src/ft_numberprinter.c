/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numberprinter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:44:22 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/07 10:06:41 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/libft.h"

int	numberprinter(int fd, unsigned int num)
{
	char	*strnum;
	int		len;

	len = 0;
	strnum = ft_itoa(num);
	ft_putstr_fd(strnum, fd);
	len = ft_strlen(strnum);
	free(strnum);
	return (len);
}
