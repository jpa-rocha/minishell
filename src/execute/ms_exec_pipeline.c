/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:01:55 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/16 17:41:29 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ms_pipe_builtins(t_shell *shell);

int	ms_top_pipe(t_shell *shell)
{
	if (pipe(shell->cmd->pfd) == -1)
		return (3);
	if (shell->cmd->cmd_idx == shell->cmd->n_cmd - 1)
	{
		if (dup2(shell->cmd->output, STDOUT_FILENO) == -1)
			return (4);
	}
	else
	{
		if (dup2(shell->cmd->pfd[1], STDOUT_FILENO) == -1)
			return (4);
		close(shell->cmd->pfd[1]);
	}
	return (0);
}

int	ms_bot_pipe(t_shell *shell)
{
	if (dup2(shell->cmd->pfd[0], STDIN_FILENO) == -1)
		return (4);
	close(shell->cmd->pfd[0]);
	if (shell->cmd->builtin_num > -2)
	{
		if (ms_next_cmd(shell) == -1)
		{
			return (EXIT_FAILURE);
		}
	}
	else
		shell->cmd->cmd_idx += 1;
	return (EXIT_SUCCESS);
}

int	ms_cmd_executing(t_shell *shell)
{
	int	error;

	if (shell->cmd->builtin_num == -1 && shell->cmd->curr_cmd[0] != NULL)
	{
		shell->status = ms_cmd_separator(shell);
		if (shell->status != EXIT_SUCCESS)
		{
			error = shell->status;
			if (error == COMMAND_NOT_FOUND)
				ft_printf(STDERR_FILENO,
					"%s%s", shell->cmd->curr_cmd[0], ERR_INV);
			ms_shell_cleanup(shell);
			exit(error);
		}
		execve(shell->cmd->cmd_name, shell->cmd->curr_cmd, shell->env);
		perror("Problem ocurred");
	}
	else
	{
		ms_pipe_builtins(shell);
	}
	return (EXIT_FAILURE);
}

static void	ms_pipe_builtins(t_shell *shell)
{
	int	exitcode;

	exitcode = 0;
	if (shell->cmd->builtin_num == 9)
		exitcode = 1;
	if (shell->cmd->builtin_num == -10)
	{
		ms_shell_cleanup(shell);
		exit(exitcode);
	}
	else
		if (shell->cmd->curr_cmd[0] != NULL && shell->cmd->builtin_num < 8)
			ms_call_built_in(shell);
	ms_shell_cleanup(shell);
	exit(exitcode);
}
