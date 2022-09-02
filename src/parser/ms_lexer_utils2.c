/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:44:34 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/02 10:28:38 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* checks whether pipe is in quotes */
int	check_char_in_quotes(char *str)
{
	size_t	i;
	int	quotes_flag;
	int index;

	quotes_flag = 0;
	index = 0;
	i = 0;
	while (str[i])
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
	while (str[i])
	{
		if (str[i] == '|' && quotes_flag == 0)
		{
			quotes_flag = 1;
			break ;
		}
		i--;
	}
	return (quotes_flag);
}

int	check_pipe_in_quotes(char *str)
{
	if (check_char_in_quotes(str) == 1)
	{
		//printf("in quotes\n");
		return (1);
	}
	//printf("not in quotes\n");
	return (0);
}

/* if there is nothing in btw two pipes, bash prints an error message, 
	this one is used in lexer function */
int	if_pipes_are_empty(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == PIPE)
		{
			i++;
			while (cmd->line[i] == ' ' || cmd->line[i] == '\t')
				i++;
			if (cmd->line[i] == PIPE)
			{
				printf(ERR_MU, "|");
				return (EXIT_FAILURE);
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}


int	count_pipes(t_cmd *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == PIPE)
			count += 1;
		i++;
	}
	return (count);
}

/* if we pass just pipes, nothing else as arguments, bash prints error messages */
int	check_if_only_pipe(t_cmd *cmd)
{
	int	i;
	int	c;
	
	c = count_pipes(cmd);
	i = 0;
	while (cmd->line[i] == ' ')
		i++;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == PIPE && cmd->line[i + 1] == '\0')
		{
			printf(ERR_MU, "|");
			return (EXIT_FAILURE);
		}
		else if (cmd->line[i] == PIPE && cmd->line[i + 1] == ' ')
		{
			printf(ERR_MU, "|");
			return (EXIT_FAILURE);
		}
		else if (cmd->line[i] == PIPE && c > 1 && cmd->line[i + 1] != ' ')
		{
			printf(ERR_MU, "||");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}


/* finds  dollar sign in the string
 + if env comes after we need to get env variable
 + if ? comes after we need to get exit status of the previous command call
 + if '$ENV' prints $ENV but if "$ENV" , print env variable
 + same also for $?
 */
/* char	*check_d_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == DOLLAR)
			return (&str[i]);
		i++;	
	}
	return (0);
} */