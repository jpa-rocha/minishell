/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stringprinter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:45:18 by jrocha            #+#    #+#             */
/*   Updated: 2022/03/18 13:01:49 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header/libft.h"

int	stringprinter(char *s)
{
	char	*nullcase;

	nullcase = "(null)";
	if (s == NULL)
	{
		ft_putstr_fd(nullcase, 1);
		return (ft_strlen(nullcase));
	}
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}
