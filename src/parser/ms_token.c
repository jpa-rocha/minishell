/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:22:34 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/19 12:19:35 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
static int	ms_is_in_quotes(char *str, size_t idx, int c)
{
	int		quotes_flag;
	int		index;
	size_t	i;

	i = 0;
	quotes_flag = 0;
	index = 0;
	while (i < idx)
	{
		if ((str[i] == SQ || str[i] == DQ) && quotes_flag == 0)
		{
			quotes_flag = 1;
			break ;
		}
		i++;
	}
	i++;
	while (i < ft_strlen(str))
	{
		if ((str[i] == SQ || str[i] == DQ) && quotes_flag == 1)
		{
			index += i;
			quotes_flag = 0;
			break ;
		}
		i++;
	}
	i = index - 1;
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
} */

static int	count_break_q(char *str, int i, int count)
{
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && check_char_in_quotes(str, i, str[i]) == 0)
			count++;
		i++;
	}
	return (count);
}

static int	check_new(char **new)
{
	if (new == NULL)
		return (0);
	return (0);
}

static char	**break_quotes(t_shell *shell, char *str)
{
	int		i;
	int		j;
	int		k;
	char	**new;
	int		count;

	i = 0;
	j = 0;
	count = 1;
	count = count_break_q(str, i, count);
	new = ft_calloc(count + 1, sizeof(char *));
	check_new(new);
	i = 0;
	k = 0;
	while (k < count)
	{
		if ((str[i] == ' ' && check_char_in_quotes(str, i, ' ') == 0)
			|| str[i] == '\0')
		{
			new[k] = ft_calloc(j + 1, sizeof(char));
			ft_strlcpy(new[k], &str[i - j], j + 1);
			new[k] = (char *)ms_dollar_check(shell, new[k]);
			new[k] = check_quotes_pre_lexer(new[k]);
			k++;
			j = -1;
		}
		j++;
		i++;
	}
	new[k] = NULL;
	return (new);
}

static char	**prepare_lexer(char **lexer)
{
	int		len;
	int		i;
	char	**new;

	i = 0;
	len = ms_args_len(lexer);
	new = ft_calloc(len + 1, sizeof(char *));
	while (i < len)
	{
		new[i] = remove_white_spaces(lexer[i]);
		i += 1;
	}
	ms_free_args(lexer);
	return (new);
}

char	***create_seq_from_lexer(t_shell *shell)
{
	int	j;

	j = 0;
	shell->lexer = prepare_lexer(shell->lexer);
	shell->cmd->seq = ft_calloc(ms_args_len(shell->lexer) + 1, sizeof(char *));
	while (j < shell->cmd->n_cmd)
	{
		shell->cmd->seq[j] = break_quotes(shell, shell->lexer[j]);
		j++;
	}
	shell->cmd->seq[j] = NULL;
	return (shell->cmd->seq);
}
