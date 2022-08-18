/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:50:08 by jrocha            #+#    #+#             */
/*   Updated: 2022/08/18 10:59:14 by jrocha           ###   ########.fr       */
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

	if (ms_args_len(shell->cmd->args) >= 1)
	{
		check = ms_exec_first_check(shell);
		if (check != 0)
			return (shell->exitcode);
	}
	return (ms_valid_command(shell));
}

// Check if there are arguments, and if so if they are printable characters
// MIGHT BE MADE UNUSABLE BY LEXER
static int	ms_exec_first_check(t_shell *shell)
{
	if (ft_strlen(shell->cmd->args[0]) == 1
		&& (shell->cmd->args[0][0] <= 32 || shell->cmd->args[0][0] == 58))
		shell->exitcode = EXIT_FAILURE;
	else if (ft_strlen(shell->cmd->args[0]) == 1
		&& shell->cmd->args[0][0] == 33)
		shell->exitcode = EXIT_FAILURE;
	else
		shell->exitcode = EXIT_SUCCESS;
	return (shell->exitcode);
}

// Check if arguments are valid commands, if not print error
// message and return
static int	ms_valid_command(t_shell *shell)
{
	int	i;

	i = 0;
	while (i <= ms_args_len(shell->cmd->args) && ms_args_len(shell->cmd->args) > 0)
	{
		if (ms_is_built_in(shell, shell->cmd->args[i]) == 0)
			return (ms_call_built_in(shell));
		// FORK WILL BE HERE - BUT WHICH COMMANDS NEED TO BE FORKED?
		// UNLESS ITS A BUILTIN THE REAL PATH NEEDS TO BE CHECKED		
		else if (access(shell->cmd->args[i], F_OK) == -1)
		{
			printf("%s%s", shell->cmd->args[i], ERR_INV);
			return (COMMAND_NOT_FOUND);
		}
		else if (access(shell->cmd->args[i], F_OK) != -1)
		{
			execve(BI_PATH, shell->cmd->args, shell->env);
			perror("Problem ocurred");
			return (EXIT_SUCCESS);
		}
		i += 1;
	}
	return (2);
}

static int ms_is_built_in(t_shell *shell, char *builtin)
{
	char *builtins[BI_NUM];
	int i;

	i = 0;
	builtins[0] = "exit";
	builtins[1] = "env";
	builtins[2] = "echo";
	builtins[3] = "pwd";
	builtins[4] = "export";
	builtins[5] = "unset";
	builtins[6] = "cd";
	builtins[7] = "minishell";
	while (i < 8)
	{
		if (ft_strncmp(builtins[i], builtin, ft_strlen(builtin)) == 0)
		{
			shell->cmd->builtin_num = i;
			return (EXIT_SUCCESS);
		}
		i += 1;
	}
	shell->cmd->builtin_num = -1;
	return (EXIT_FAILURE);
}

static int	ms_call_built_in(t_shell *shell)
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
		return (ms_export(shell, shell->cmd->args[1]));
	if (shell->cmd->builtin_num == 5)
		return (ms_unset(shell, shell->cmd->args[1]));
	if (shell->cmd->builtin_num == 6)
		return (ms_cd(shell, shell->cmd->args));
	if (shell->cmd->builtin_num == 7)
		return (ms_shell(shell->env, shell->argv));
	return (EXIT_FAILURE);
}