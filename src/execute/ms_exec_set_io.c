/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_set_io.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:33:07 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/21 17:00:15 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_exec_set_input(t_shell *shell, int i);
static int	ms_exec_set_output(t_shell *shell);
static int	ms_exec_outs(t_shell *shell, int i);
static int	ms_exec_ins(t_shell *shell, int i);

int	ms_exec_set_in_out(t_shell *shell)
{
	int		cmd_len;
	char	**cmd;
	int		i;

	if (shell->cmd->builtin_num < -1)
		return (ms_exec_error(shell));
	i = 0;
	cmd = shell->cmd->curr_cmd;
	cmd_len = ms_args_len(shell->cmd->curr_cmd);
	while (i < cmd_len)
	{
		if (ft_strchr(cmd[i], '<') != NULL)
			ms_exec_set_input(shell, i);
		cmd = shell->cmd->curr_cmd;
		if (ft_strchr(cmd[i], '>') != NULL)
			ms_exec_set_output(shell);
		else
		{
			shell->cmd->input = shell->cmd->temp_fd[0];
			shell->cmd->output = shell->cmd->temp_fd[1];
		}
		cmd_len = ms_args_len(shell->cmd->curr_cmd);
		i += 1;
	}
	return (EXIT_SUCCESS);
}

static int	ms_exec_set_input(t_shell *shell, int i)
{
	int		error;
	int		cmd_len;

	cmd_len = ms_args_len(shell->cmd->curr_cmd);
	while (i < cmd_len)
	{
		if (ft_strchr(shell->cmd->curr_cmd[i], '<') != NULL)
		{
			ms_exec_ins(shell, i);
			error = ms_cmd_replace_in(shell, shell->cmd->curr_cmd, i);
			cmd_len = ms_args_len(shell->cmd->curr_cmd);
			i = -1;
		}
		close(shell->cmd->input);
		if (error != EXIT_SUCCESS)
			return (error);
		i += 1;
	}
	return (EXIT_SUCCESS);
}

static int	ms_exec_ins(t_shell *shell, int i)
{
	if (shell->cmd->input != shell->cmd->temp_fd[0])
		close(shell->cmd->input);
	if (ft_strncmp(shell->cmd->curr_cmd[i], "<<", 2) == 0)
	{
		if (ms_exec_here_doc_fork(shell, i) == 130)
				shell->cmd->builtin_num = -11;
	}
	else
		shell->cmd->input = open(shell->cmd->curr_cmd[i + 1], O_RDONLY);
	if (shell->cmd->input < 0)
		return (-1);
	if (dup2(shell->cmd->input, STDIN_FILENO) == -1)
		return (-1);
	return (EXIT_SUCCESS);
}

static int	ms_exec_set_output(t_shell *shell)
{
	int	cmd_len;
	int	error;
	int	i;

	i = 0;
	error = 0;
	cmd_len = ms_args_len(shell->cmd->curr_cmd);
	while (i < cmd_len)
	{
		cmd_len = ms_args_len(shell->cmd->curr_cmd);
		if (ft_strchr(shell->cmd->curr_cmd[i], '>') != NULL)
		{
			error = ms_exec_outs(shell, i);
			if (error == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i = -1;
		}
		cmd_len = ms_args_len(shell->cmd->curr_cmd);
		i += 1;
	}
	if (error != EXIT_SUCCESS)
		return (error);
	return (EXIT_SUCCESS);
}

static int	ms_exec_outs(t_shell *shell, int i)
{
	if (shell->cmd->output != shell->cmd->temp_fd[1])
		close(shell->cmd->output);
	if (ft_strncmp(shell->cmd->curr_cmd[i], ">>", 2) == 0)
		shell->cmd->output = open(shell->cmd->curr_cmd[i + 1],
				O_RDWR | O_CREAT | O_APPEND, 00777);
	else
		shell->cmd->output = open(shell->cmd->curr_cmd[i + 1],
				O_WRONLY | O_CREAT | O_TRUNC, 00777);
	if (shell->cmd->output < 0)
		return (EXIT_FAILURE);
	if (ms_cmd_replace_out(shell, shell->cmd->curr_cmd, i) == 1)
		return (EXIT_FAILURE);
	return (0);
}
