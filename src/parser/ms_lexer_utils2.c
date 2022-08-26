/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:44:34 by mgulenay          #+#    #+#             */
/*   Updated: 2022/08/24 12:29:22 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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