/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:50:08 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/15 16:28:10 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_command_processing(t_shell *shell);

int	ms_exec(t_shell *shell)
{
	shell->cmd->temp_fd[0] = dup(STDIN_FILENO);
	shell->cmd->temp_fd[1] = dup(STDOUT_FILENO);
	shell->cmd->input = shell->cmd->temp_fd[0];
	shell->cmd->output = shell->cmd->temp_fd[1];
	if (shell->cmd->curr_cmd != NULL)
		ms_free_args(shell->cmd->curr_cmd);
	shell->cmd->curr_cmd = ms_copy_cmd(shell->cmd->seq[shell->cmd->cmd_idx]);
	if (shell->cmd->curr_cmd == NULL)
		return (EXIT_FAILURE);
	shell->status = ms_command_processing(shell);
	dup2(shell->cmd->temp_fd[0], STDIN_FILENO);
	dup2(shell->cmd->temp_fd[1], STDOUT_FILENO);
	close(shell->cmd->temp_fd[0]);
	close(shell->cmd->temp_fd[1]);
	close(shell->cmd->input);
	close(shell->cmd->output);
	return (shell->status);
}

// Check if there are arguments, and if so if they are printable characters

// Check if arguments are valid commands, if not print error
// message and return
static int	ms_command_processing(t_shell *shell)
{
	int		error;

	while (shell->cmd->cmd_idx < shell->cmd->n_cmd)
	{
		if (ms_exec_set_in_out(shell) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		ms_is_built_in(shell, shell->cmd->curr_cmd);
		error = ms_top_pipe(shell);
		if (error != EXIT_SUCCESS)
			return (error);
		if (shell->cmd->cmd_idx == 0 && shell->cmd->changes_state == 1)
			ms_call_built_in(shell);
		else
		{
			shell->pid = fork();
			ms_signals_child();
			if (shell->pid == 0)
			{
				ms_cmd_executing(shell);
			}
			else if (shell->pid > 0)
			{
				waitpid(-1, &shell->status, 0);
				ms_signals_parent();
				if (WIFSIGNALED(shell->status) == 1)
					shell->status = 128 + WTERMSIG(shell->status);
				else
					shell->status = WEXITSTATUS(shell->status);
			}
			else
				return (EXIT_FAILURE);
		}
		error = ms_bot_pipe(shell);
		if (error != 0)
			return (error);
	}
	return (shell->status);
}

