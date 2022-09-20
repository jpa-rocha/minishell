/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:49:47 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/20 14:59:10 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_char_in_quotes_first_check(char *str, int idx,
				t_qcheck *check);
static int	check_char_in_quotes_second_check(char *str, int idx, int c,
				t_qcheck *check);

int	check_char_in_quotes(char *str, int idx, int c)
{
	t_qcheck	*check;

	check = ft_calloc(1, sizeof(t_qcheck));
	check->i = 0;
	check->quotes_flag = 0;
	check->firstq = 0;
	check->secondq = 0;
	while (str[check->i] != '\0')
	{
		check_char_in_quotes_first_check(str, idx, check);
		if (check_char_in_quotes_second_check(str, idx, c, check) == 1)
		{
			free(check);
			return (1);
		}
		check->i += 1;
	}
	free(check);
	return (0);
}

static void	check_char_in_quotes_first_check(char *str, int idx,
	t_qcheck *check)
{
	if ((str[check->i] == SQ || str[check->i] == DQ)
		&& check->quotes_flag == 0 && check->i < idx)
	{
		check->quotes_flag = 1;
		check->firstq = check->i;
		check->i += 1;
	}
	if (str[check->i] == str[check->firstq] && check->quotes_flag > 0)
	{
		if (check->i > idx)
		{
			check->quotes_flag = 2;
			check->secondq = check->i;
		}
		else
		{
			check->quotes_flag = 0;
			check->firstq = check->i;
		}
	}
}

static int	check_char_in_quotes_second_check(char *str, int idx, int c,
	t_qcheck *check)
{
	if (check->quotes_flag == 2 && check->secondq > idx)
	{
		check->iter = check->firstq;
		while (check->iter < check->secondq)
		{
			if (str[check->iter] == c)
			{
				return (1);
			}
			check->iter += 1;
		}
	}
	return (0);
}
