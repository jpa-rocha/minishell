/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:50:08 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/15 10:08:59 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_is_built_in(t_shell *shell, char **curr_cmd);
static int	ms_exec_first_check(t_shell *shell);
static int	ms_command_processing(t_shell *shell);
static int	ms_control_state(t_shell *shell, char **curr_cmd);

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
// MIGHT BE MADE UNUSABLE BY LEXER
static int	ms_exec_first_check(t_shell *shell)
{
	if (ft_strlen(shell->cmd->curr_cmd[0]) < 1
		|| (shell->cmd->curr_cmd[0][0] <= 32
		|| shell->cmd->curr_cmd[0][0] == 58))
	{
		shell->cmd->builtin_num = 8;
		return (EXIT_SUCCESS);
	}
	else if (ft_strlen(shell->cmd->curr_cmd[0]) == 1
		&& shell->cmd->curr_cmd[0][0] == 33)
	{
		shell->cmd->builtin_num = 9;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

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
			if (shell->pid == -1)
				return (EXIT_FAILURE);
			if (shell->pid == 0)
			{
				ms_pid_setter(shell->pid);
				ms_cmd_executing(shell);
			}
			waitpid(-1, &shell->status, 0);
			shell->status = WEXITSTATUS(shell->status);
			ms_pid_setter(-1);
			ms_signals();
		}
		error = ms_bot_pipe(shell);
		if (error != 0)
			return (error);
	}
	return (shell->status);
}

static int	ms_is_built_in(t_shell *shell, char **curr_cmd)
{
	int		i;
	char	*mini;
	int		check;

	i = 0;
	mini = "./minishell";
	check = ms_exec_first_check(shell);
	if (check == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	while (i < BI_NUM)
	{
		if (curr_cmd[0] != NULL && ft_strncmp(shell->builtins[i], curr_cmd[0],
				ft_strlen(shell->builtins[i])) == 0)
		{
			shell->cmd->builtin_num = i;
			shell->cmd->changes_state = ms_control_state(shell, curr_cmd);
			return (EXIT_SUCCESS);
		}
		i += 1;
	}
	if (curr_cmd[0] != NULL
		&& ft_strncmp(mini, curr_cmd[0], ft_strlen(mini)) == 0)
	{
		shell->cmd->builtin_num = 2;
		shell->cmd->changes_state = ms_control_state(shell, curr_cmd);
		return (EXIT_SUCCESS);
	}
	shell->cmd->builtin_num = -1;
	shell->cmd->changes_state = ms_control_state(shell, curr_cmd);
	return (EXIT_FAILURE);
}

static int	ms_control_state(t_shell *shell, char **curr_cmd)
{
	if (shell->cmd->builtin_num <= 2 && shell->cmd->builtin_num >= 0)
		return (1);
	else if (shell->cmd->builtin_num == 3 || shell->cmd->builtin_num == 4)
	{
		if (ms_args_len(curr_cmd) > 1)
			return (1);
	}
	else
		return (0);
	return (0);
}

int	ms_call_built_in(t_shell *shell)
{
	if (shell->cmd->builtin_num == 0)
		return (ms_cd(shell, shell->cmd->curr_cmd));
	if (shell->cmd->builtin_num == 1)
		return (ms_exit(shell));
	if (shell->cmd->builtin_num == 2)
		return (ms_shell(shell->env, shell->argv, shell->shlvl + 1, -1));
	if (shell->cmd->builtin_num == 3)
		return (ms_export(shell, shell->cmd->curr_cmd));
	if (shell->cmd->builtin_num == 4)
		return (ms_unset(shell, shell->cmd->curr_cmd));
	if (shell->cmd->builtin_num == 5)
		return (ms_echo(shell->cmd));
	if (shell->cmd->builtin_num == 6)
		return (ms_pwd());
	if (shell->cmd->builtin_num == 7)
		return (ms_env(shell));
	return (EXIT_FAILURE);
}
