/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:05:45 by mgulenay          #+#    #+#             */
/*   Updated: 2022/08/24 19:35:24 by mgulenay         ###   ########.fr       */
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
	shell->cmd->args = shell->lexer;
	if (shell->cmd->args == NULL)
	{
		shell->exitcode = ALLOCATION_PROBLEM_EXIT;
		return (shell->exitcode);
	}
/* 	int a = get_nmb_cmd(shell->cmd);
	printf("%d\n", a); */
	
	print_nb_words(shell);

 	char ***a;
	a = create_seq_from_lexer(shell);
	printf("%s\n", **a);
	return (EXIT_SUCCESS);
}
