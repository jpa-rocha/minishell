/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:42:44 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/16 11:27:48 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_exec_replace_out_inner(char **cmd, char **new_cmd, int len);
static int	ms_exec_replace_in_inner(char **cmd, char **new_cmd, int len);

int	ms_cmd_replace_in(t_shell *shell, char **cmd)
{
	char	**new_cmd;
	int		len;
	int		exit;

	len = ms_args_len(cmd);
	new_cmd = ft_calloc(len - 1, sizeof(char *));
	if (new_cmd == NULL)
		return (ALLOCATION_PROBLEM_EXIT);
	exit = ms_exec_replace_in_inner(cmd, new_cmd, len);
	if (exit != EXIT_SUCCESS)
		return (ALLOCATION_PROBLEM_EXIT);
	ms_free_args(shell->cmd->curr_cmd);
	shell->cmd->curr_cmd = new_cmd;
	return (EXIT_SUCCESS);
}

static int	ms_exec_replace_in_inner(char **cmd, char **new_cmd, int len)
{
	int		i;
	int		j;

	i = 0;
	j = 2;
	if (cmd[0][0] == '<')
	{
		while (j < len)
		{
			new_cmd[i] = ft_strdup(cmd[j]);
			i += 1;
			j += 1;
		}
		new_cmd[i] = NULL;
	}
	else
	{
		while (i < len - 2)
		{
			new_cmd[i] = ft_strdup(cmd[i]);
			i += 1;
		}
		new_cmd[i] = NULL;
	}
	return (EXIT_SUCCESS);
}

int	ms_cmd_replace_out(t_shell *shell, char **cmd)
{
	char	**new_cmd;
	int		len;
	int		term;

	len = ms_args_len(cmd);
	new_cmd = ft_calloc(len, sizeof(char *));
	if (new_cmd == NULL)
		return (ALLOCATION_PROBLEM_EXIT);
	term = ms_exec_replace_out_inner(cmd, new_cmd, len);
	new_cmd[term] = NULL;
	ms_free_args(shell->cmd->curr_cmd);
	shell->cmd->curr_cmd = new_cmd;
	return (EXIT_SUCCESS);
}

static int	ms_exec_replace_out_inner(char **cmd, char **new_cmd, int len)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	while (i < len)
	{
		if (ft_strchr(cmd[i], '>') != NULL && flag == 0)
		{
			i += 2;
			flag = 1;
		}
		if (j < len - 2)
			new_cmd[j] = ft_strdup(cmd[i]);
		i += 1;
		j += 1;
	}
	return (j);
}
