/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:22:34 by mgulenay          #+#    #+#             */
/*   Updated: 2022/08/27 10:59:48 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* need to remove quotes for printing if it is already closed: 
 -- first check, if already in double or single quote, then remove it, 
-- if we have a case like : 
	echo "hello 'world' ", 
we need to remove just the double quote
*/

bool	sq_closed(char *str)
{
	int	i;
	int	quote_end;
	int	sq_closed;

	sq_closed = false;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == SQ)
		{
			quote_end = i + 1;
			while (str[i] && (str[quote_end] != str[i]))
			{
				if (str[quote_end] == SQ)
				{
					sq_closed = true;
				}
				quote_end++;
			}
			i = quote_end;
		}
		i++;
	}
	return (true);
}

bool	dq_closed(char *str)
{
	int	i;
	int	quote_end;
	int	dq_closed;

	dq_closed = false;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == DQ)
		{
			quote_end = i + 1;
			while (str[i] && (str[quote_end] != str[i]))
			{
				if (str[quote_end] == SQ)
				{
					dq_closed = true;
				}
				quote_end++;
			}
			i = quote_end;
		}
		i++;
	}
	return (true);

}

void	check_quotes_for_lexer(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == SQ && sq_closed(str))
			remove_sq(str);
		else if (str[i] == DQ && dq_closed(str))
			remove_dq(str);
		i++;				
	}
}

char	*remove_sq(char *str)
{
	char	*temp;
	int		i;
	int		k;
	char	c;
	
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		c = str[i];
		if (c == '\'')
		{
			i++;
			temp = ft_calloc(ft_strlen(str) - 2 + 1, sizeof(char));
			while (str[i] != '\0' && str[i] != '\'')
			{
				temp[k] = str[i];					
				k++;
				i++;
			}
		}			
		i++;
	}
	temp[k] = '\0';
	str = ft_strdup(temp);
	printf("%s\n", str);
	return(str);
}

char	*remove_dq(char *str)
{
	char	*temp;
	int		i;
	int		k;
	char	c;
	
	i = 0;
	k = 0;
	while (str[i] != '\0')
	{
		c = str[i];
		if (c == '\"')
		{
			i++;
			temp = ft_calloc(ft_strlen(str) - 2 + 1, sizeof(char));
			while (str[i] != '\0' && str[i] != '\"')
			{
				temp[k] = str[i];		
				k++;
				i++;
			}
		}
		i++;
	}
	temp[k] = '\0';
	str = ft_strdup(temp);
	free(temp);
	printf("%s\n", str);
	return (str);
}

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
	//int	total;

	//total = 0;
	j = 0;
	while (j < shell->cmd->n_cmd)
	{
		shell->cmd->n_words = count_words(shell->lexer[j]);
		//total += shell->n_words;
		j++;
	}
	//return (total);
	return (shell->cmd->n_words);
}

char	**get_each_word(char *str)
{
	// hello world --
	char **words;
	int	i;

	int num_words = 0; // 2
	int num_chars = 0; // length of each word --  5 

	i = 0;
	words = (char **)malloc(sizeof(char *) * count_words(str) + 1);
		while (num_words < count_words(str))
		{
			words[num_words] = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
			while (str[i] != ' ' && str[i] != '\t' && str[i] != '\0')
			{
    			words[num_words][num_chars] = str[i];
				num_chars += 1;
				i++;
			}
			if(str[i] == ' ' || str[i] == '\t')
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
	int	j; // number of strings in lexer variable
	
	j = 0;
	shell->cmd->seq = ft_calloc(ms_args_len(shell->lexer), sizeof(char *));
	while (j < shell->cmd->n_cmd)
	{
		shell->cmd->seq[j] = get_each_word(shell->lexer[j]); 
		j++;
	}
	//printf("ok\n");
	return (shell->cmd->seq);
}
