/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:22:34 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/02 16:59:11 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* count number of words in a string */
int	count_words(char *str)
{
	int		i;
	int		nb_words;
	char	c;
	
	if (ft_strlen(str) > 0)
		c = str[0];
	nb_words = 1;
	i = 0;
	while (str[i])
	{
		if ((str[i] == ' ' || str[i] == '\t') && c != ' ')
			nb_words += 1;
		c = str[i];
		i++;
	}
	return (nb_words);
}

/* print number of words in each lexer[nb_cmd] */
void	print_nb_words(t_shell *shell)
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
}

/* get number of words in each lexer[nb_cmd] */
/* int	get_nb_words_store(t_shell *shell)
{
	int j;
	//int	total;

	//total = 0;
	j = 0;
	while (j < shell->cmd->n_cmd)
	{
		shell->cmd->n_words = count_words(shell->lexer[j]);
		//total += shell->n_words;
		printf("%d\n", shell->cmd->n_words);
		j++;
	}
	//return (total);
	return (shell->cmd->n_words);
} */

char	**get_each_word(char *str)
{
	char	**words;
	int		i;
	int		num_words;
	size_t	num_chars;
	
	num_words = 0;
	num_chars = 0;
	i = 0;
	//words = (char **)malloc(sizeof(char *) * count_words(str) + 1);
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
	j = 0;
	while (j < shell->cmd->n_cmd)
	{
		//shell->lexer[j] = check_quotes_pre_lexer(shell->lexer[j]);
		shell->cmd->seq[j] = get_each_word(shell->lexer[j]); 
		j++;
	}
	shell->cmd->seq[j] = NULL;
	return (shell->cmd->seq);
}
