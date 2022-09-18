/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 10:16:45 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/16 14:06:43 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_exec_cmd_check(t_shell *shell);

// CHECKS FOR NULL COMMAND TEST
int	ms_cmd_separator(t_shell *shell)
{
	if (shell->cmd->cmd_idx < shell->cmd->n_cmd)
	{
		if (shell->cmd->curr_cmd[0] != NULL)
		{
			if (access(shell->cmd->curr_cmd[0], F_OK) == 0)
				shell->cmd->cmd_name = ft_strdup(shell->cmd->curr_cmd[0]);
			else if (ms_find_cmd_loop(shell) == EXIT_FAILURE)
			{
				return (COMMAND_NOT_FOUND);
			}
		}
	}
	return (EXIT_SUCCESS);
}

// Checks if command exists in the path variables
int	ms_find_cmd_loop(t_shell *shell)
{
	if (shell->cmd->cmd_name != NULL)
	{
		free(shell->cmd->cmd_name);
		shell->cmd->cmd_name = NULL;
	}
	if (ms_exec_cmd_check(shell) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static int	ms_exec_cmd_check(t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*cmd;

	i = 0;
	while (shell->cmd->path[i] != NULL)
	{
		tmp = ft_strjoin(shell->cmd->path[i], "/");
		cmd = ft_strjoin(tmp, shell->cmd->curr_cmd[0]);
		if (access(cmd, F_OK) == 0)
		{
			shell->cmd->cmd_name = ft_strdup(cmd);
			free(tmp);
			free(cmd);
			return (EXIT_SUCCESS);
		}
		if (tmp != NULL)
			free(tmp);
		if (cmd != NULL)
			free(cmd);
		i++;
	}
	return (EXIT_FAILURE);
}

int	ms_next_cmd(t_shell *shell)
{
	if (shell->cmd->cmd_name != NULL)
	{
		free(shell->cmd->cmd_name);
		shell->cmd->cmd_name = NULL;
	}
	shell->cmd->cmd_idx += 1;
	if (shell->cmd->curr_cmd != NULL)
		ms_free_args(shell->cmd->curr_cmd);
	shell->cmd->curr_cmd = ms_copy_cmd(shell->cmd->seq[shell->cmd->cmd_idx]);
	return (ms_cmd_separator(shell));
}
