/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:44:34 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/05 12:31:29 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	check_char_in_quotes(char *str);

/* checks whether pipe is in quotes */
static int	check_char_in_quotes(char *str)
{
	size_t	i;
	int		quotes_flag;
	int		index;

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
	while (i < ft_strlen(str))
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

/* check */
int	check_pipe_in_quotes(char *str)
{
	if (check_char_in_quotes(str) == 1)
		return (1);
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
			while (cmd->line[i] == ' ')
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