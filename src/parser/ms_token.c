/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:22:34 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/20 15:35:20 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**break_quotes_inner_loop(t_shell *shell,
				char *str, t_breaks *b);
static int	count_break_q(char *str, t_breaks *breaks);

static char	**break_quotes(t_shell *shell, char *str)
{
	t_breaks	*b;
	char		**new;

	b = ft_calloc(1, sizeof(t_breaks));
	b->i = 0;
	b->j = 0;
	b->k = 0;
	b->count = count_break_q(str, b);
	new = break_quotes_inner_loop(shell, str, b);
	new[b->k] = NULL;
	free(b);
	return (new);
}

static char	**break_quotes_inner_loop(t_shell *shell,
			char *str, t_breaks *b)
{
	char		**new;

	new = ft_calloc(b->count + 1, sizeof(char *));
	if (new == NULL)
		return (NULL);
	while (b->k < b->count)
	{
		if ((str[b->i] == ' ' && check_char_in_quotes(str, b->i, ' ') == 0)
			|| str[b->i] == '\0')
		{
			new[b->k] = ft_calloc(b->j + 1, sizeof(char));
			ft_strlcpy(new[b->k], &str[b->i - b->j], b->j + 1);
			new[b->k] = (char *)ms_dollar_check(shell, new[b->k]);
			new[b->k] = check_quotes_pre_lexer(new[b->k]);
			b->k++;
			b->j = -1;
		}
		b->j++;
		b->i++;
	}
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

static int	count_break_q(char *str, t_breaks *breaks)
{
	int	i;

	i = 0;
	breaks->count = 1;
	while (str[i] != '\0')
	{
		if (str[i] == ' '
			&& check_char_in_quotes(str, i, str[i]) == 0)
			breaks->count++;
		i++;
	}
	return (breaks->count);
}
