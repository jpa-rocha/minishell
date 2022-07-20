/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:50:08 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/20 12:56:17 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_is_built_in(t_shell *shell, char *builtin);
static int	ms_call_built_in(t_shell *shell);
static int	ms_exec_first_check(t_shell *shell);

static int	ms_valid_command(t_shell *shell);

int	ms_exec(t_shell *shell)
{
	int	check;

	if (ms_args_len(shell->cmd->args) == 1)
	{
		check = ms_exec_first_check(shell);
		if (check != 2)
			return (shell->exitcode);
	}
	return (ms_valid_command(shell));
}

static int	ms_exec_first_check(t_shell *shell)
{
	int	exitcode;

	if (ft_strlen(shell->cmd->args[0]) == 1
		&& (shell->cmd->args[0][0] <= 32 || shell->cmd->args[0][0] == 58))
		exitcode = 0;
	else if (ft_strlen(shell->cmd->args[0]) == 1
		&& shell->cmd->args[0][0] == 33)
		exitcode = 1;
	else
		exitcode = 2;
	if (exitcode != 2)
		shell->exitcode = exitcode;
	return (exitcode);
}

// Check if arguments are valid commands, if not print error
// message and return
static int	ms_valid_command(t_shell *shell)
{
	int	i;

	i = 0;
	while (i <= ms_args_len(shell->cmd->args) && ms_args_len(shell->cmd->args) > 0)
	{
		if (ms_is_built_in(shell, shell->cmd->args[i]) == 1)
			return (ms_call_built_in(shell));
		else if (access(shell->cmd->args[i], F_OK) == -1)
		{
			printf("%s%s", shell->cmd->args[i], ERR_INV);
			return (127);
		}
		else if (access(shell->cmd->args[i], F_OK) != -1)
		{
			execve("./src/built_ins/env", shell->cmd->args, shell->env);
			perror("Problem ocurred");
			return (EXIT_SUCCESS);
		}
		i += 1;
	}
	return (2);
}

static int	ms_is_built_in(t_shell *shell, char *builtin)
{
	if (ft_strncmp(builtin, "exit", ft_strlen(builtin)) == 0)
	{
		shell->cmd->builtin_num = 1;
		return (1);
	}
	if (ft_strncmp(builtin, "env", ft_strlen(builtin)) == 0)
	{
		shell->cmd->builtin_num = 2;
		return (1);
	}
	if (ft_strncmp(builtin, "echo", ft_strlen(builtin)) == 0)
	{
		shell->cmd->builtin_num = 3;
		return (1);
	}
	if (ft_strncmp(builtin, "pwd", ft_strlen(builtin)) == 0)
	{
		shell->cmd->builtin_num = 4;
		return (1);
	}
	if (ft_strncmp(builtin, "export", ft_strlen(builtin)) == 0)
	{
		shell->cmd->builtin_num = 5;
		return (1);
	}
	if (ft_strncmp(builtin, "unset", ft_strlen(builtin)) == 0)
	{
		shell->cmd->builtin_num = 6;
		return (1);
	}
	if (ft_strncmp(builtin, "cd", ft_strlen(builtin)) == 0)
	{
		shell->cmd->builtin_num = 7;
		return (1);
	}
	if (ft_strncmp(builtin, "./minishell", ft_strlen(builtin)) == 0)
	{
		shell->cmd->builtin_num = 8;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ms_call_built_in(t_shell *shell)
{
	if (shell->cmd->builtin_num == 1)
		return (ms_exit(shell));
	if (shell->cmd->builtin_num == 2)
		return (ms_env(shell));
	if (shell->cmd->builtin_num == 3)
		return (ms_echo(shell->cmd));
	if (shell->cmd->builtin_num == 4)
		return (ms_pwd());
	if (shell->cmd->builtin_num == 5)
		return (ms_export(shell, shell->cmd->args[1]));
	if (shell->cmd->builtin_num == 6)
		return (ms_unset(shell, shell->cmd->args[1]));
	if (shell->cmd->builtin_num == 7)
		return (ms_cd(shell, shell->cmd->args[1]));
	if (shell->cmd->builtin_num == 8)
		return (ms_shell(shell->env, shell->argv));
	return (EXIT_FAILURE);
}