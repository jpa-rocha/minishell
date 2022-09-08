/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:22:34 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/08 22:57:41 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *str);

/* count number of words in a string */
static int	count_words(char *str)
{
	int		i;
	int		nb_words;
	char	c;
	
	if (ft_strlen(str) > 0)
		c = str[0];
	nb_words = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == ' ' || str[i] == '\t') && c != ' ')
			nb_words += 1;
		c = str[i];
		i++;
	}
	return (nb_words);
}

/* print number of words in each lexer[nb_cmd] */
/* void	print_nb_words(t_shell *shell)
{
	int j;
	int c;

	j = 0;
	while (j < shell->cmd->n_cmd)
	{
		c = count_words(shell->lexer[j]);
		printf("index [%d] has [%d] words\n", j, c);
		j++;
	}
} */

static int	check_q(char *str)
{
	size_t	i;
	int		quotes_flag;
	int		index;

	quotes_flag = 0;
	index = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] ==  SQ || str[i] ==  DQ) && quotes_flag == 0)
		{
			quotes_flag = 1;
			break ;
		}
		i++;
	}
	i++;
	while (i < ft_strlen(str))
	{
		if ((str[i] == SQ || str[i] ==  DQ) && quotes_flag == 1)
		{
			index += i;
			quotes_flag = 0;
			break ;
		}
		i++;
	}
	return (quotes_flag);
}

char	*remove_white_spaces(char *str)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i] != '\0')
	{
		if (str[i] == ' ' && str[i + 1] && str[i + 1] == ' ' && check_q(str) == 0)
		{
			i++;
			continue;
		}
		new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	str = ft_strdup(new_str);
	free(new_str);
	return (str);
}

/* char	*remove_white_spaces(char *str)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i] != '\0')
	{
		if ((str[i] == ' ' && str[i + 1] == ' ') == 0)
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	str = ft_strdup(new_str);
	free(new_str);
	return (str);
}
 */
char	**get_each_word(char *str)
{
	char	**words;
	size_t	i;

	int num_words = 0;
	size_t num_chars = 0;
	i = 0;
	words = ft_calloc(count_words(str) + 1, sizeof(char *));
	while (num_words < count_words(str))
	{
		words[num_words] = ft_calloc(ft_strlen(str) + 1, sizeof(char));
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
		{
			words[num_words][num_chars] = str[i];
			num_chars += 1;
			i++;
		}
		if(str[i] == ' ' || str[i] == '\t' || num_chars == ft_strlen(&str[i]))
		{
			words[num_words][num_chars] = '\0';
			num_chars = 0;
		}
		i++;
		num_words++;
	}
	words[num_words] = NULL;
	return (words);
}

/* 
lexer[number of pipes filled with string][length of each string]
seq[number of pipes filled with string][number of words in each string][length of each words]
*/

/* hi ho | no why
lexer[0] = hi ho   -- words[0][2] = hi, words[1][2] = ho
lexer[1] = no why -- words[0][2] = no, words[1][3] = why 

seq[0][2][] => seq[0][0][2] = hi, seq[0][1][2] = ho 
seq[1][2][] => seq[1][0][2] = no, seq[1][1][3] = why
*/

char	***create_seq_from_lexer(t_shell *shell)
{
	int	j;
	
	j = 0;
	shell->cmd->seq = ft_calloc(ms_args_len(shell->lexer) + 1, sizeof(char *));
	while (j < shell->cmd->n_cmd)
	{
		//if (check_char_in_quotes(shell->lexer[j], ' ') == 0)
		shell->lexer[j] = remove_white_spaces(shell->lexer[j]);
		shell->lexer[j] = check_quotes_pre_lexer(shell->lexer[j]);
		shell->cmd->seq[j] = get_each_word(shell->lexer[j]);
		j++;
	}
	shell->cmd->seq[j] = NULL;
	return (shell->cmd->seq);
}
