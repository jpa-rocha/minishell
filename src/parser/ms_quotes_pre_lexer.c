/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_pre_lexer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 14:38:50 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/20 15:47:54 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*sq_if_helper(char *str, int index, size_t i, int d_flag);
static char	*dq_if_helper(char *str, int index, size_t i, int s_flag);
static char	*check_quotes_pre_lexer_sq(char *str, t_lexcheck *lex);
static char	*check_quotes_pre_lexer_dq(char *str, t_lexcheck *lex);

char	*check_quotes_pre_lexer(char *str)
{
	t_lexcheck	*lex;

	lex = ft_calloc(1, sizeof(t_lexcheck));
	lex->index = 0;
	lex->i = 0;
	while (str[lex->i] != '\0')
	{
		lex->s_flag = flag_quotes(str, SQ);
		lex->d_flag = flag_quotes(str, DQ);
		if (str[lex->i] == SQ && lex->s_flag == 0)
			str = check_quotes_pre_lexer_sq(str, lex);
		else if (str[lex->i] == DQ && lex->d_flag == 0)
			str = check_quotes_pre_lexer_dq(str, lex);
		lex->i++;
	}
	free(lex);
	return (str);
}

static char	*check_quotes_pre_lexer_sq(char *str, t_lexcheck *lex)
{
	str = sq_if_helper(str, lex->index, lex->i, lex->d_flag);
	if (flag_quotes(str, SQ) == 0)
	{
		lex->index = lex->i;
		lex->index++;
		while (str[lex->index] != SQ)
				lex->index++;
		str = remove_quotes(str, lex->i, SQ);
		lex->i = lex->index;
		lex->i -= 2;
	}
	return (str);
}

static char	*check_quotes_pre_lexer_dq(char *str, t_lexcheck *lex)
{
	str = dq_if_helper(str, lex->index, lex->i, lex->s_flag);
	if (flag_quotes(str, DQ) == 0)
	{
		lex->index = lex->i;
		lex->index++;
		while (str[lex->index] != DQ && str[lex->index] != '\0')
			lex->index++;
		str = remove_quotes(str, lex->i, DQ);
		lex->i = lex->index;
		lex->i -= 2;
	}
	return (str);
}

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
