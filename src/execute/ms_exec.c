/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:50:08 by jrocha            #+#    #+#             */
/*   Updated: 2022/08/30 15:38:36 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_is_built_in(t_shell *shell, char **curr_cmd);
static int	ms_exec_first_check(t_shell *shell);
static int	ms_command_processing(t_shell *shell);

int	ms_exec(t_shell *shell)
{
	int	check;
	int	tmp_fd[2];

	tmp_fd[0] = dup(0);
	tmp_fd[1] = dup(1);
	shell->cmd->curr_cmd = shell->cmd->seq[shell->cmd->cmd_idx];
	check = ms_exec_first_check(shell);
	if (check != 0)
		return (shell->exitcode);
	if (shell->cmd->seq != NULL)
		shell->cmd->curr_cmd = shell->cmd->seq[shell->cmd->cmd_idx];
	else
		return (EXIT_FAILURE);
	shell->exitcode = ms_command_processing(shell);
	dup2(tmp_fd[0], STDIN_FILENO);
	dup2(tmp_fd[1], STDOUT_FILENO);
	close(tmp_fd[0]);
	close(tmp_fd[1]);
	return (shell->exitcode);
}

// Check if there are arguments, and if so if they are printable characters
// MIGHT BE MADE UNUSABLE BY LEXER
static int	ms_exec_first_check(t_shell *shell)
{
	if (ft_strlen(shell->cmd->curr_cmd[0]) < 1
		|| (shell->cmd->curr_cmd[0][0] <= 32 ||
		shell->cmd->curr_cmd[0][0] == 58))
		return (EXIT_FAILURE);
	else if (ft_strlen(shell->cmd->curr_cmd[0]) == 1
		&& shell->cmd->curr_cmd[0][0] == 33)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// Check if arguments are valid commands, if not print error
// message and return
static int	ms_command_processing(t_shell *shell)
{
	int	pid;

	if (ms_exec_set_in_out(shell, shell->cmd->seq) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (shell->cmd->cmd_idx < shell->cmd->n_cmd)
	{
		if (shell->cmd->cmd_idx > 0)
			shell->cmd->rdir_idx = 0;
		if (shell->cmd->n_cmd == 1 && ms_is_built_in(shell, shell->cmd->curr_cmd) == 0)
			return (ms_call_built_in(shell));
		// FORK WILL BE HERE - BUT WHICH COMMANDS NEED TO BE FORKED?
		// UNLESS ITS A BUILTIN THE REAL PATH NEEDS TO BE CHECKED
		if (shell->cmd->builtin_num == -1)
		{
			shell->exitcode = ms_cmd_separator(shell);
			if (shell->exitcode != EXIT_SUCCESS)
				return (shell->exitcode);
		}
		shell->exitcode = ms_top_pipe(shell);
		if (shell->exitcode != 0)
			return (shell->exitcode);
		pid = fork();
		if (pid == -1)
			return (EXIT_FAILURE);
		if (pid == 0)
			ms_cmd_executing(shell);
		waitpid(-1, &shell->exitcode, 0);
		shell->exitcode = ms_bot_pipe(shell);
		if (shell->exitcode != 0)
			return (shell->exitcode);
	}
	return (shell->exitcode);
}

static int ms_is_built_in(t_shell *shell, char **curr_cmd)
{
	char	*builtins[BI_NUM];
	int		i;

	i = 0;
	builtins[0] = "exit";
	builtins[1] = "env";
	builtins[2] = "echo";
	builtins[3] = "pwd";
	builtins[4] = "export";
	builtins[5] = "unset";
	builtins[6] = "cd";
	builtins[7] = "minishell";
	while (i < BI_NUM)
	{
		if (ft_strncmp(builtins[i], curr_cmd[shell->cmd->rdir_idx],
				ft_strlen(builtins[i])) == 0)
		{
			shell->cmd->builtin_num = i;
			return (EXIT_SUCCESS);
		}
		i += 1;
	}
	shell->cmd->builtin_num = -1;
	return (EXIT_FAILURE);
}

int	ms_call_built_in(t_shell *shell)
{
	if (shell->cmd->builtin_num == 0)
		return (ms_exit(shell));
	if (shell->cmd->builtin_num == 1)
		return (ms_env(shell));
	if (shell->cmd->builtin_num == 2)
		return (ms_echo(shell->cmd));
	if (shell->cmd->builtin_num == 3)
		return (ms_pwd());
	if (shell->cmd->builtin_num == 4)
		return (ms_export(shell, shell->cmd->curr_cmd));
	if (shell->cmd->builtin_num == 5)
		return (ms_unset(shell, shell->cmd->curr_cmd));
	if (shell->cmd->builtin_num == 6)
		return (ms_cd(shell, shell->cmd->curr_cmd));
	if (shell->cmd->builtin_num == 7)
		return (ms_shell(shell->env, shell->argv));
	return (EXIT_FAILURE);
}
