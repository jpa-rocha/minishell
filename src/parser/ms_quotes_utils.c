/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:49:47 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/18 20:58:38 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				while (str[index] != DQ)
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
