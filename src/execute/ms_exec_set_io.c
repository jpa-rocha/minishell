/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_set_io.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 09:33:07 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/20 11:29:45 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_exec_set_input(t_shell *shell);
static int	ms_exec_set_output(t_shell *shell);
static int	ms_exec_outs(t_shell *shell, int i);
static int	ms_exec_error(t_shell *shell);

int	ms_exec_set_in_out(t_shell *shell)
{
	int		cmd_len;
	char	**cmd;

	if (shell->cmd->builtin_num < -1)
		return (ms_exec_error(shell));
	cmd = shell->cmd->curr_cmd;
	cmd_len = ms_args_len(shell->cmd->curr_cmd);
	if ((cmd[0][0] == '<' && ft_strlen(cmd[0]) == 1 && cmd[1] != NULL)
		|| ft_strncmp(cmd[0], "<<", 2) == 0)
		ms_exec_set_input(shell);
	cmd_len = ms_args_len(shell->cmd->curr_cmd);
	cmd = shell->cmd->curr_cmd;
	if (cmd_len >= 3 && cmd[cmd_len - 2][0] == '>'
		&& (ft_strlen(cmd[cmd_len - 2]) == 1
		|| ft_strncmp(cmd[cmd_len - 2], ">>", 2) == 0))
		ms_exec_set_output(shell);
	else
	{
		shell->cmd->input = shell->cmd->temp_fd[0];
		shell->cmd->output = shell->cmd->temp_fd[1];
	}
	return (EXIT_SUCCESS);
}

static int	ms_exec_error(t_shell *shell)
{
	shell->cmd->input = shell->cmd->temp_fd[0];
	shell->cmd->output = shell->cmd->temp_fd[1];
	return (EXIT_SUCCESS);
}

static int	ms_exec_set_input(t_shell *shell)
{
	int		error;

	while (ft_strchr(shell->cmd->curr_cmd[0], '<') != NULL)
	{
		if (shell->cmd->input != shell->cmd->temp_fd[0])
			close(shell->cmd->input);
		if (ft_strncmp(shell->cmd->curr_cmd[0], "<<", 2) == 0)
		{
			if (ms_exec_here_doc_fork(shell) == 130)
				shell->cmd->builtin_num = -11;
		}
		else
			shell->cmd->input = open(shell->cmd->curr_cmd[1], O_RDONLY);
		if (shell->cmd->input < 0)
			return (-1);
		if (dup2(shell->cmd->input, STDIN_FILENO) == -1)
			return (-1);
		error = ms_cmd_replace_in(shell, shell->cmd->curr_cmd);
	}
	close(shell->cmd->input);
	if (error != EXIT_SUCCESS)
		return (error);
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
		if (shell->cmd->curr_cmd[i] != NULL
			&& ft_strchr(shell->cmd->curr_cmd[i], '>') != NULL)
		{
			error = ms_exec_outs(shell, i);
			if (error == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i -= 1;
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
	if (ms_cmd_replace_out(shell, shell->cmd->curr_cmd) == 1)
		return (EXIT_FAILURE);
	return (0);
}
