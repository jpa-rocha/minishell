/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexprinter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:47:03 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 12:59:42 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/libft.h"

int	hexprinter(char *flags, unsigned int num)
{
	char	*hexnum;
	int		i;

	i = 0;
	hexnum = ft_convert2hexa(num);
	if (flags[ft_strlen(flags) - 1] == 'X')
	{
		while (hexnum[i] != '\0')
		{
			hexnum[i] = ft_toupper(hexnum[i]);
			i++;
		}
	}
	ft_putstr_fd(hexnum, 1);
	i = ft_strlen(hexnum);
	free(hexnum);
	return (i);
}
