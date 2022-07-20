/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:02:26 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/19 18:41:05 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ms_parser(t_shell *shell)
{
	shell->exitcode = ms_lexer(shell);
/* 	shell->cmd->args = ft_split(shell->cmd->line, ' ');
	if (shell->cmd->args == NULL)
	{
		shell->exitcode = ALLOCATION_PROBLEM_EXIT;
		return (shell->exitcode);
	}  */
	return (0);
}