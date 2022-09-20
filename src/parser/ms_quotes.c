/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 11:51:08 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/20 11:55:57 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	quotes_len(char *str)
{
	size_t	len;

	if (ft_strncmp(str, "", 0) == 1)
		len = ft_strlen(str);
	else
		len = 0;
	return (len);
}

static void	flag_quotes_helper(char *str, size_t i, size_t len, int quote)
{
	int	quotes_flag;

	quotes_flag = 0;
	while (i < len && str[i] != '\0')
	{
		if ((str[i] == quote) && quotes_flag == 0)
		{
			quotes_flag = 1;
			break ;
		}
		i++;
	}
}

int	flag_quotes(char *str, int quote)
{
	size_t	i;
	size_t	len;
	int		quotes_flag;

	quotes_flag = 0;
	len = quotes_len(str);
	i = 0;
	flag_quotes_helper(str, i, len, quote);
	i++;
	while (i < len && str[i] != '\0')
	{
		if ((str[i] == quote) && quotes_flag == 1)
		{
			quotes_flag = 0;
			break ;
		}
		i++;
	}
	return (quotes_flag);
}
