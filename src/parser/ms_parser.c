/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:02:26 by jrocha            #+#    #+#             */
/*   Updated: 2022/08/15 18:28:03 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ms_parser(t_shell *shell)
{
	if (shell->cmd->line != NULL)
		shell->exitcode = ms_lexer(shell);
	char *t = get_each_token(shell);
	printf("%s\n", t);
/* 	shell->cmd->args = ft_split(shell->cmd->line, ' ');
	if (shell->cmd->args == NULL)
	{
		shell->exitcode = ALLOCATION_PROBLEM_EXIT;
		return (shell->exitcode);
	}  */
	return (EXIT_SUCCESS);
}