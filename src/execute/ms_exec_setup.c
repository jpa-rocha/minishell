/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:16:45 by jrocha            #+#    #+#             */
/*   Updated: 2022/08/25 20:51:50 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_find_cmd_loop(t_shell *shell);
static int	ms_cmd_separator(t_shell *shell);
static int	ms_next_cmd(t_shell *shell);

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
	close(STDOUT_FILENO);
	close(shell->cmd->pfd[0]);
	if (ms_next_cmd(shell) == -1)
	{
		shell->exitcode = EXIT_FAILURE;
		return (shell->exitcode);
	}
	return (EXIT_SUCCESS);
}

int	ms_cmd_executing(t_shell *shell)
{
	if (shell->cmd->builtin_num == -1)
	{
		execve(shell->cmd->cmd_name, shell->cmd->curr_cmd, shell->env);
		perror("Problem ocurred");
	}
	else
		return (ms_call_built_in(shell));
	return (EXIT_FAILURE);
}

//NEEDS TO BE CHECKED IT WILL WORK ACCORDING TO EVALSHEET
static int	ms_cmd_separator(t_shell *shell)
{
	char	*cmdctrl;
	
	if (shell->cmd->cmd_idx <= shell->cmd->n_cmd)
	{
		cmdctrl = ft_strrchr(shell->cmd->curr_cmd[shell->cmd->rdir_idx], '/');
		if (cmdctrl != NULL)
		{
			cmdctrl++;
			shell->cmd->cmd_name = cmdctrl;
		}
		if (ms_find_cmd_loop(shell) == EXIT_FAILURE)
		{
			printf("%s%s", shell->cmd->curr_cmd[shell->cmd->rdir_idx], ERR_INV);
			return (COMMAND_NOT_FOUND);
		}
	}
	return (0);
}

// Checks if command exists in the path variables
static int	ms_find_cmd_loop(t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*cmd;

	i = 0;
	while (shell->cmd->path[i] != NULL)
	{
		tmp = ft_strjoin(shell->cmd->path[i], "/");
		cmd = ft_strjoin(tmp, shell->cmd->curr_cmd[shell->cmd->rdir_idx]);
		if (access(cmd, F_OK) == 0)
		{
			shell->cmd->cmd_name = ft_strdup(cmd);
			free(tmp);
			free(cmd);
			return (0);
		}
		if (tmp != NULL)
			free(tmp);
		if (cmd != NULL)
			free(cmd);
		i++;
	}
	return (EXIT_FAILURE);
}

static int	ms_next_cmd(t_shell *shell)
{
	if (shell->cmd->cmd_name != NULL)
		free(shell->cmd->cmd_name);
	shell->cmd->cmd_idx += 1;
	shell->cmd->curr_cmd = shell->cmd->seq[shell->cmd->cmd_idx];
	return (ms_cmd_separator(shell));
}
