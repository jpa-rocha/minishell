/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:50:08 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/11 16:03:25 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_is_built_in(t_shell *shell, char *builtin);
static int	ms_call_built_in(t_shell *shell);

static int	ms_valid_command(t_shell *shell);

int ms_exec(t_shell *shell)
{
  if (ms_valid_command(shell) != 0)
    return (1);
  return (0);
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
			return (1);
		}
		else if (access(shell->cmd->args[i], F_OK) != -1)
		{
			printf("%s: lets do it\n", shell->cmd->args[i]);
			return (0);
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
	return (0);
}

static int	ms_call_built_in(t_shell *shell)
{
	if (shell->cmd->builtin_num == 1)
		return (ms_exit(shell->cmd));
	if (shell->cmd->builtin_num == 2)
		return (ms_env(shell->workenv));
	if (shell->cmd->builtin_num == 3)
		return (ms_echo(shell->cmd));
	if (shell->cmd->builtin_num == 4)
		return (ms_pwd());
	if (shell->cmd->builtin_num == 5)
		return (ms_export(shell, shell->workenv, shell->cmd->args[1]));
	return(1);
}