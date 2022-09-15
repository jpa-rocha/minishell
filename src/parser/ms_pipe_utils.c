/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:44:34 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/15 10:08:08 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* checks whether pipe is inside the quotes */

int	check_char_in_quotes(char *str, int idx, int c)
{
	int		quotes_flag;
	int		firstq;
	int		secondq;
	int		iter;
	int		i;

	i = 0;
	quotes_flag = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == SQ || str[i] == DQ) && quotes_flag == 0 && i < idx)
		{
			quotes_flag = 1;
			firstq = i;
			i += 1;
		}
		if (str[i] == str[firstq] && quotes_flag > 0)
		{
			if (i > idx)
			{
				quotes_flag = 2;
				secondq = i;
			}
			else
			{
				quotes_flag = 0;
				firstq = i;
			}
		}
		if (quotes_flag == 2 && secondq > idx)
		{
			iter = firstq;
			while (iter < secondq)
			{
				if (str[iter] == c)
					return (1);
				iter += 1;
			}
		}
		i += 1;	
	}
	return (0);
}

/* {
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
		//else
		//	return (0);
		i++;
	}
	i++;
	while (i < ft_strlen(str))
	{
		if ((str[i] == SQ || str[i] == DQ) && quotes_flag == 1 && i > idx)
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
}
 */
/* int	check_char_in_quotes(char *str, char c)
{
	size_t	i;
	int		quotes_flag;
	int		index;

	quotes_flag = 0;
	index = 0;
	i = 0;
	while (str[i] != '\0')
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

/* check */
/* int	check_pipe_in_quotes(char *str)
{
	if (check_char_in_quotes(str, PIPE) == 1)
		return (1);
	return (0);
} */

/* if there is nothing btw two pipes, bash prints an error message */
int	check_empty_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == PIPE \
			&& check_char_in_quotes(cmd->line, i, PIPE) == 0)
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

static int	count_pipes(t_cmd *cmd)
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

/* if we just write pipes, bash prints error messages
 (it should give the same error msg with echo cmd) 
*/
int	check_pipes(t_cmd *cmd)
{
	int	i;
	int	c;

	c = count_pipes(cmd);
	i = 0;
	while (cmd->line[i] == ' ')
		i++;
	while (cmd->line[i] != '\0' && cmd->line[i] == PIPE)
	{
		if (cmd->line[i] == PIPE && cmd->line[i + 1] == '\0' \
			&& check_char_in_quotes(cmd->line, i, PIPE) == 0)
		{
			printf(ERR_MU, "|");
			return (EXIT_FAILURE);
		}
		else if (cmd->line[i] == PIPE && cmd->line[i + 1] == ' ' \
			&& check_char_in_quotes(cmd->line, i, PIPE) == 0)
		{
			printf(ERR_MU, "|");
			return (EXIT_FAILURE);
		}
		else if (cmd->line[i] == PIPE && c > 1 && cmd->line[i + 1] != ' ' \
			&& check_char_in_quotes(cmd->line, i, PIPE) == 0)
		{
			printf(ERR_MU, "||");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
