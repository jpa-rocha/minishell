/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsignedprinter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:42:22 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 13:02:49 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/libft.h"

int	unsignedprinter(unsigned int num)
{
	char	*strnum;
	int		len;

	len = 0;
	strnum = ft_utoa(num);
	ft_putstr_fd(strnum, 1);
	len = ft_strlen(strnum);
	free(strnum);
	return (len);
}
