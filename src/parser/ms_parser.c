/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:05:45 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/05 12:22:35 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* prints substrings within the lexer */
void	print_lexer(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->lexer[i])
	{
		printf("[%d] %s\n", i, shell->lexer[i]);
		i++;
	}
}

int	ms_parser(t_shell *shell)
{
	if (shell->cmd->line != NULL)
		shell->exitcode = ms_lexer(shell);
	shell->cmd->seq = create_seq_from_lexer(shell);
	if (shell->cmd->seq == NULL)
	{
		shell->exitcode = ALLOCATION_PROBLEM_EXIT;
		return (shell->exitcode);
	}
	ms_free_args(shell->lexer);
	shell->lexer = NULL;
	return (EXIT_SUCCESS);
}
