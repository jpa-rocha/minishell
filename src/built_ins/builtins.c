/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 16:21:21 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/22 12:39:21 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_exec_first_check(t_shell *shell);
static int	ms_builtin_shell_control(t_shell *shell, char **curr_cmd);

int	ms_is_built_in(t_shell *shell, char **curr_cmd)
{
	int		i;
	int		check;

	i = 0;
	check = ms_exec_first_check(shell);
	if (check == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	while (i < BI_NUM)
	{
		if (curr_cmd[0] != NULL && ft_strncmp(shell->builtins[i], curr_cmd[0],
				ft_strlen(curr_cmd[0])) == 0)
		{
			shell->cmd->builtin_num = i;
			shell->cmd->changes_state = ms_control_state(shell, curr_cmd);
			return (EXIT_SUCCESS);
		}
		i += 1;
	}
	check = ms_builtin_shell_control(shell, curr_cmd);
	if (check == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	shell->cmd->builtin_num = -1;
	shell->cmd->changes_state = ms_control_state(shell, curr_cmd);
	return (EXIT_FAILURE);
}

static int	ms_builtin_shell_control(t_shell *shell, char **curr_cmd)
{
	int		len;

	if (curr_cmd[0] != NULL)
	{	
		len = ft_strlen(curr_cmd[0]) - 1;
		while (len >= 0 && curr_cmd[0][len] != '/')
			len -= 1;
		if (ft_strncmp(shell->builtins[2], &curr_cmd[0][len + 1],
			ft_strlen(shell->builtins[2])) == 0
		&& access(curr_cmd[0], F_OK) == 0)
		{
			shell->cmd->builtin_num = 2;
			shell->cmd->changes_state = ms_control_state(shell, curr_cmd);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}

int	ms_control_state(t_shell *shell, char **curr_cmd)
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
	if (shell->cmd->builtin_num < -1)
		return (ms_error_messages(shell, shell->cmd->builtin_num));
	if (shell->cmd->builtin_num == 0)
		return (ms_cd(shell, shell->cmd->curr_cmd));
	if (shell->cmd->builtin_num == 1)
		return (ms_exit(shell, shell->cmd->curr_cmd));
	if (shell->cmd->builtin_num == 2)
		return (ms_shell(shell->env, shell->argv, shell->shlvl + 1));
	if (shell->cmd->builtin_num == 3)
		return (ms_export(shell, shell->cmd->curr_cmd));
	if (shell->cmd->builtin_num == 4)
		return (ms_unset(shell, shell->cmd->curr_cmd));
	if (shell->cmd->builtin_num == 5)
		return (ms_echo(shell->cmd));
	if (shell->cmd->builtin_num == 6)
		return (ms_pwd(shell));
	if (shell->cmd->builtin_num == 7)
		return (ms_env(shell));
	return (EXIT_FAILURE);
}

static int	ms_exec_first_check(t_shell *shell)
{
	if (shell->cmd->builtin_num < -1)
		return (EXIT_SUCCESS);
	if (shell->cmd->curr_cmd == NULL)
	{
		if (shell->cmd->builtin_num > -1)
			shell->cmd->builtin_num = 10;
		return (EXIT_SUCCESS);
	}
	if (shell->cmd->curr_cmd[0] != NULL)
	{
		if (ft_strlen(shell->cmd->curr_cmd[0]) == 1
			&& shell->cmd->curr_cmd[0][0] == 33)
		{
			shell->cmd->builtin_num = -16;
			return (EXIT_SUCCESS);
		}
		else if (ft_strlen(shell->cmd->curr_cmd[0]) == 1
			|| (shell->cmd->curr_cmd[0][0] <= 32
			|| shell->cmd->curr_cmd[0][0] == 58))
		{
			shell->cmd->builtin_num = -17;
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_FAILURE);
}
