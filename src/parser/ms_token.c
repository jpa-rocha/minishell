/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:22:34 by mgulenay          #+#    #+#             */
/*   Updated: 2022/08/24 22:50:41 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* need to remove quotes for printing if it is already closed: 
 -- first check, if already in double or single quote, then remove it, 
-- if we have a case like : 
	echo "hello 'world' ", 
we need to remove just the double quote
*/
/* sub_string is needs to be created from lexer , 
in this case : echo , "hello" */
/*  void	check_remove_quotes(t_shell **sub_string)
{
	char	*new_str;
	int		i;
	int		k;
	char	c;
	
	i = 0;
	k = 0;
	new_str = ft_strdup(*sub_string);
	while (sub_string[i])
	{
		c = sub_string[i];
		if (c == SQ || c == DQ )
		{
			i++;
			while (sub_string[i])
			{
				new_str[k] = sub_string[i];
				k++;
				i++;
			}
		}
	}
	new_str[k] = '\0';
} */

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
int	get_nb_words_store(t_shell *shell)
{
	int j;

	j = 0;
	while (j < shell->cmd->n_cmd)
	{
		shell->n_words = count_words(shell->lexer[j]);
		j++;
	}
	return (shell->n_words);
}

char	*get_each_word(char *str)
{
	int		i;
	int		j;
	int		nb_words;
	char	c;
	char	*temp;

	temp = malloc(sizeof(char) * ft_strlen(str));
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] != ' ' && str[i] != '\t'))
			temp[j] = str[i]; 
		else if ((str[i] == ' ' || str[i] == '\t'))
			temp[j] = str[i];
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

/* 
lexer[number of pipes filled with string][length of each string]
seq[number of pipes filled with string][number of words in each string][length of each words]
*/
char	***create_seq_from_lexer(t_shell *shell)
{
	int	i; //length of each words
	int	j; // number of pipes filled with string
	int	k; // number of words in each string

	j = 0;
	k = 0;
	shell->seq = (char ***)malloc(sizeof(char **) * shell->n_words + 1);
	while (j < shell->cmd->n_cmd)
	{
		shell->seq[j] = (char **)malloc(sizeof(char *) * shell->n_words + 1);
		shell->seq[j] = shell->lexer[j];
		while (k < shell->n_words)
		{
			shell->seq[j][k] = (char *)malloc(sizeof(char ) * shell->n_words + 1);
			shell->seq[j][k] = 
			k++;
		}
		shell->seq[k][i] = (char *)malloc(size_t(char) * 10 + 1);
		shell->seq[k][i] = shell->lexer[j];
		j++;
	}
	printf("ok\n");
	return (shell->seq);
}

/* char	*get_each_token(t_shell *shell)
{
	int		i;
	int		j;
	int		k;
	int		m;

	i = 0;
	j = 0;
	k = 0;
	m = 0;
	while (shell->lexer[j])
	{
		shell->sub_string = ft_calloc();
		while (shell->sub_string[k])
		{
			while (shell->sub_string[k][i])
			{
				shell->single_str= malloc(sizeof(char) * 20 + 1);
				if (shell->sub_string[k][i] != ' ')
				{
					shell->single_str[m] = shell->sub_string[k][i];
					m++;
				}
				else if (shell->sub_string[k][i] == ' ')
				{
					shell->single_str[m] = shell->sub_string[k][i + 1];
					m++;
				}
				i++;
			}
			shell->single_str[m] = '\0';
			k++;
		}
		j++;
	}
	return (shell->single_str);
}
 */