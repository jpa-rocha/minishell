/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:49:47 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/20 13:03:38 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_char_in_quotes(char *str, int idx, int c)
{
	int		quotes_flag;
	int		firstq;
	int		secondq;
	int		iter;
	int		i;

	i = 0;
	quotes_flag = 0;
	firstq = 0;
	secondq = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == SQ || str[i] == DQ) && quotes_flag == 0 && i < idx)
		{
			quotes_flag = 1;
			firstq = i;
			i += 1;
		}
		if (str[i] == str[firstq] && quotes_flag > 0)
		{
			if (i > idx)
			{
				quotes_flag = 2;
				secondq = i;
			}
			else
			{
				quotes_flag = 0;
				firstq = i;
			}
		}
		if (quotes_flag == 2 && secondq > idx)
		{
			iter = firstq;
			while (iter < secondq)
			{
				if (str[iter] == c)
					return (1);
				iter += 1;
			}
		}
		i += 1;
	}
	return (0);
}

/* checks whether a char is inside the quotes */
/* int	check_char_in_quotes(char *str, int idx, int c)
{
	int		quotes_flag;
	int		quotes[2];
	int		iter;
	int		i;

	i = 0;
	quotes_flag = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == SQ || str[i] == DQ) && quotes_flag == 0 && i < idx)
		{
			quotes_flag = 1;
			quotes[0] = i;
			i += 1;
		}
		if (str[i] == str[quotes[0]] && quotes_flag > 0)
		{
			if (i > idx)
			{
				quotes_flag = 2;
				quotes[1] = i;
			}
			else
			{
				quotes_flag = 0;
				quotes[0] = i;
			}
		}
		if (quotes_flag == 2 && quotes[1] > idx)
		{
			iter = quotes[0];
			while (iter < quotes[1])
			{
				if (str[iter] == c)
					return (1);
				iter += 1;
			}
		}
		i += 1;
	}
	return (0);
} */

static char	*sq_if_helper(char *str, int index, size_t i, int d_flag)
{
	while (str[i] != '\0' && str[i] != SQ)
	{
		if (str[i] == DQ && d_flag == 0)
		{
			index = i;
			index++;
			while (str[index] != SQ)
				index++;
			str = remove_quotes(str, i, SQ);
			i = index;
		}
		i++;
	}
	return (str);
}

static char	*dq_if_helper(char *str, int index, size_t i, int s_flag)
{
	while (str[i] != '\0' && str[i] != DQ)
	{
		if (str[i] == SQ && s_flag == 0)
		{
			index = i;
			index++;
			while (str[index] != DQ)
				index++;
			str = remove_quotes(str, i, DQ);
			i = index;
		}
		i++;
	}
	return (str);
}

char	*check_quotes_pre_lexer(char *str)
{
	size_t		i;
	int			index;
	int			s_flag;
	int			d_flag;

	index = 0;
	i = 0;
	while (str[i] != '\0')
	{
		s_flag = flag_quotes(str, SQ);
		d_flag = flag_quotes(str, DQ);
		if (str[i] == SQ && s_flag == 0)
		{
			str = sq_if_helper(str, index, i, d_flag);
			if (flag_quotes(str, SQ) == 0)
			{
				index = i;
				index++;
				while (str[index] != SQ)
						index++;
				str = remove_quotes(str, i, SQ);
				i = index;
				i -= 2;
			}
		}
		else if (str[i] == DQ && d_flag == 0)
		{
			str = dq_if_helper(str, index, i, s_flag);
			if (flag_quotes(str, DQ) == 0)
			{
				index = i;
				index++;
				while (str[index] != DQ && str[index] != '\0')
					index++;
				str = remove_quotes(str, i, DQ);
				i = index;
				i -= 2;
			}
		}
		i++;
	}
	return (str);
}
