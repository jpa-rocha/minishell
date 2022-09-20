/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:04:55 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/20 14:08:58 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	check_dollar_in_quotes_first_loop(char *str, size_t idx,
				size_t i, int quotes_flag);

int	check_dollar_in_quotes(char *str, size_t idx, int c)
{
	int		quotes_flag;
	size_t	i;

	i = 0;
	quotes_flag = 0;
	i = check_dollar_in_quotes_first_loop(str, idx, i, quotes_flag) - 1;
	while (i < ft_strlen(str))
	{
		if (str[i] == c && quotes_flag == 0)
		{
			quotes_flag = 1;
			break ;
		}
		i--;
	}
	return (quotes_flag);
}

static int	check_dollar_in_quotes_first_loop(char *str, size_t idx,
		size_t i, int quotes_flag)
{
	int	index;

	index = 0;
	while (i < idx)
	{
		if ((str[i] == SQ) && quotes_flag == 0)
		{
			quotes_flag = 1;
			break ;
		}
		i++;
	}
	i++;
	while (i < ft_strlen(str))
	{
		if ((str[i] == SQ) && quotes_flag == 1)
		{
			index += i;
			quotes_flag = 0;
			break ;
		}
		i++;
	}
	return (index);
}
