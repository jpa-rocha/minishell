/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:44:34 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/19 09:04:26 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* if there is nothing btw two pipes, bash prints an error message */
int	check_empty_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == PIPE
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
static int	pipes_helper(t_cmd *cmd, int i, int c)
{
	if (cmd->line[i] == PIPE && cmd->line[i + 1] == ' '
		&& check_char_in_quotes(cmd->line, i, PIPE) == 0)
	{
		cmd->builtin_num = -3;
		return (EXIT_FAILURE);
	}
	if (cmd->line[i] == PIPE && c > 1 && cmd->line[i + 1] != ' '
		&& check_char_in_quotes(cmd->line, i, PIPE) == 0)
	{
		cmd->builtin_num = -4;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

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
		if (cmd->line[i] == PIPE && cmd->line[i + 1] == '\0'
			&& check_char_in_quotes(cmd->line, i, PIPE) == 0)
		{
			cmd->builtin_num = -3;
			return (EXIT_FAILURE);
		}
		else if (pipes_helper(cmd, i, c) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
