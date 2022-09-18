/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:05:45 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/18 18:31:29 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* checks how many group of substrings we have -- the separator is the PIPE */
int	get_nmb_cmd(t_cmd *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == PIPE
			&& check_char_in_quotes(cmd->line, i, PIPE) == 0)
		{
			i += 1;
			while (cmd->line[i] == ' ' || cmd->line[i] == PIPE)
				i += 1;
			if (cmd->line[i] != '\0')
				count += 1;
			if (cmd->line[i] == '\0')
			{
				cmd->builtin_num = -10;
				return (EXIT_FAILURE);
			}
		}
		i += 1;
	}
	return (count);
}

void	alloc_lexer(t_shell *shell)
{
	shell->cmd->n_cmd = get_nmb_cmd(shell->cmd);
	shell->lexer = ft_calloc(shell->cmd->n_cmd + 1, sizeof(char *));
}

int	ms_parser(t_shell *shell)
{
	if (shell->cmd->line != NULL)
	{
		if (check_char_errors(shell->cmd) == EXIT_FAILURE)
		{
			shell->status = -2;
			shell->cmd->n_cmd = 1;
			return (EXIT_SUCCESS);
		}
		ms_lexer(shell);
	}
	shell->cmd->seq = create_seq_from_lexer(shell);
	if (shell->cmd->seq == NULL)
	{
		shell->status = ALLOCATION_PROBLEM_EXIT;
		return (shell->status);
	}
	ms_free_args(shell->lexer);
	shell->lexer = NULL;
	return (EXIT_SUCCESS);
}
