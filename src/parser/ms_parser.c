/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:02:26 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/19 12:22:32 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ms_parser(t_shell *shell)
{
	//shell->cmd->args = ft_split(shell->cmd->line, ' ')
	ms_lexer(shell);
	if (shell->cmd->args == NULL)
	{
		shell->exitcode = 12;
		return (shell->exitcode);
	}
	return (EXIT_SUCCESS);
}
