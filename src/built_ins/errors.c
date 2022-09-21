/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 12:33:38 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/21 17:02:33 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static	int	ms_more_errors(t_shell *shell, int error_num);
static	int	ms_more_more_errors(t_shell *shell, int error_num);

int	ms_error_messages(t_shell *shell, int error_num)
{
	if (error_num == -2)
		printf(ERR_QUOTES);
	if (error_num == -3)
		printf(ERR_MU, "|");
	if (error_num == -4)
		printf(ERR_MU, "||");
	if (error_num == -5)
		printf(ERR_MU, "newline");
	if (error_num == -6)
		printf(ERR_MU, "<");
	if (error_num == -7)
		printf(ERR_MU, "<<");
	if (error_num == -8)
		printf(ERR_MU, ">");
	if (error_num == -9)
		printf(ERR_MU, ">>");
	if (error_num == -10)
		printf("pipe needs argument\n");
	shell->status = 2;
	if (error_num == -11)
		printf("\n");
	if (error_num < -11)
		shell->status = ms_more_errors(shell, error_num);
	return (EXIT_SUCCESS);
}

static	int	ms_more_errors(t_shell *shell, int error_num)
{
	if (error_num == -12)
	{
		printf(ERR_ISDIR, &shell->cmd->line[shell->cmd->error_inc]);
		return (IS_DIR_SLASH);
	}
	if (error_num == -13)
	{
		printf(ERR_NF, &shell->cmd->line[shell->cmd->error_inc]);
		return (COMMAND_NOT_FOUND);
	}
	if (error_num == -15)
	{
		shell->cmd->cmd_idx = shell->cmd->n_cmd;
		return (ERR_CWD);
	}
	if (error_num < -15)
		shell->status = ms_more_more_errors(shell, error_num);
	return (shell->status);
}

static	int	ms_more_more_errors(t_shell *shell, int error_num)
{
	if (error_num == -16)
	{
		shell->status = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	if (error_num == -17)
	{
		shell->status = EXIT_SUCCESS;
		return (EXIT_SUCCESS);
	}
	return (shell->status);
}
