/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:42:44 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/21 16:59:54 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_exec_replace_out_inner(char **cmd, char **new_cmd, int len,
				int i);
static int	ms_exec_replace_in_inner(char **cmd, char **new_cmd, int len,
				int i);

int	ms_cmd_replace_in(t_shell *shell, char **cmd, int i)
{
	char	**new_cmd;
	int		len;
	int		exit;

	len = ms_args_len(cmd);
	new_cmd = ft_calloc(len - 1, sizeof(char *));
	if (new_cmd == NULL)
		return (ALLOCATION_PROBLEM_EXIT);
	exit = ms_exec_replace_in_inner(cmd, new_cmd, len, i);
	if (exit != EXIT_SUCCESS)
		return (ALLOCATION_PROBLEM_EXIT);
	ms_free_args(shell->cmd->curr_cmd);
	shell->cmd->curr_cmd = new_cmd;
	return (EXIT_SUCCESS);
}

static int	ms_exec_replace_in_inner(char **cmd, char **new_cmd, int len, int i)
{
	int		k;
	int		j;

	k = 0;
	j = i + 2;
	while (k < i)
	{
		new_cmd[k] = ft_strdup(cmd[k]);
		k += 1;
	}
	while (j < len)
	{
		new_cmd[k] = ft_strdup(cmd[j]);
		k += 1;
		j += 1;
	}
	new_cmd[k] = NULL;
	return (EXIT_SUCCESS);
}

int	ms_cmd_replace_out(t_shell *shell, char **cmd, int i)
{
	char	**new_cmd;
	int		len;
	int		term;

	len = ms_args_len(cmd);
	new_cmd = ft_calloc(len, sizeof(char *));
	if (new_cmd == NULL)
		return (ALLOCATION_PROBLEM_EXIT);
	term = ms_exec_replace_out_inner(cmd, new_cmd, len, i);
	if (term != EXIT_SUCCESS)
		return (ALLOCATION_PROBLEM_EXIT);
	ms_free_args(shell->cmd->curr_cmd);
	shell->cmd->curr_cmd = new_cmd;
	return (EXIT_SUCCESS);
}

static int	ms_exec_replace_out_inner(char **cmd, char **new_cmd, int len,
		int i)
{
	int		k;
	int		j;

	k = 0;
	j = i + 2;
	while (k < i)
	{
		new_cmd[k] = ft_strdup(cmd[k]);
		k += 1;
	}
	while (j < len)
	{
		new_cmd[k] = ft_strdup(cmd[j]);
		k += 1;
		j += 1;
	}
	new_cmd[k] = NULL;
	return (EXIT_SUCCESS);
}
