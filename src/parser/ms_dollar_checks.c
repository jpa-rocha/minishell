/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dollar_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:04:55 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/21 09:42:27 by jrocha           ###   ########.fr       */
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

void	*ms_dollar_rep_clean(t_dol_rep *rep)
{
	if (rep->beginning != NULL)
		free(rep->beginning);
	if (rep->search != NULL)
		free(rep->search);
	if (rep->end != NULL)
		free(rep->end);
	if (rep->replace != NULL)
		free(rep->replace);
	if (rep->temp != NULL)
		free(rep->temp);
	if (rep != NULL)
		free(rep);
	return (EXIT_SUCCESS);
}

char	*ms_replace_var_search(char *dollar)
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_calloc(ft_strlen(dollar) + 1, sizeof(char));
	while (dollar[i] != '\0' && dollar[i] != 61 && dollar[i] != 63
		&& dollar[i] != 64 && dollar[i] != 34 && dollar[i] != 35
		&& dollar[i] != 36 && dollar[i] != 37 && dollar[i] != 39
		&& dollar[i] != 42 && dollar[i] != 43 && dollar[i] != 44
		&& dollar[i] != 45 && dollar[i] != 46 && dollar[i] != 47)
	{
		ret[i] = dollar[i];
		i += 1;
	}
	return (ret);
}
