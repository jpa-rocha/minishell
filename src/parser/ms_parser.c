/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:05:45 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/13 11:11:42 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* prints substrings within the lexer */
/* void	print_lexer(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->lexer[i])
	{
		printf("[%d] %s\n", i, shell->lexer[i]);
		free(shell->lexer[i]);
		i++;
	}
} */

int	ms_parser(t_shell *shell)
{
	if (shell->cmd->line != NULL)
	{
		// why does it leak? if parser is exit-failure, it already calls error management & frees in minishell.c
		if (check_char_errors(shell, shell->cmd))
			return (shell->exitcode);
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
