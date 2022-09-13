/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:42:44 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/13 17:05:44 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"
static int	ms_cmd_replace_in(t_shell *shell, char **cmd);
static int	ms_cmd_replace_out(t_shell *shell, char **cmd);
//static int	ms_exec_cmd_check(t_shell *shell);
static int	ms_exec_set_input(t_shell *shell);
static int	ms_exec_set_output(t_shell *shell);

int	ms_exec_set_in_out(t_shell *shell)
{
	int		cmd_len;
	int		error;
	char	**cmd;

	error = 0;
	cmd = shell->cmd->curr_cmd;
	cmd_len = ms_args_len(shell->cmd->curr_cmd);
	if ((cmd[0][0] == '<' && ft_strlen(cmd[0]) == 1)
		|| ft_strncmp(cmd[0], "<<", 2) == 0)
		error = ms_exec_set_input(shell);
	cmd_len = ms_args_len(shell->cmd->curr_cmd);
	if (cmd_len >= 3 && cmd[cmd_len - 2][0] == '>'
		&& (ft_strlen(cmd[cmd_len - 2]) == 1
		|| ft_strncmp(cmd[cmd_len], ">>", 2) == 0))
		error = ms_exec_set_output(shell);
	else
	{
		shell->cmd->input = shell->cmd->temp_fd[0];
		shell->cmd->output = shell->cmd->temp_fd[1];
	}
	if (error == EXIT_SUCCESS || error == EXIT_FAILURE)
		return (error);
	return (shell->status);
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
			if (ms_exec_here_doc(shell) != 0)
				return (-1);
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
	int i;

	i = 0;
	cmd_len = ms_args_len(shell->cmd->curr_cmd);
	while (i < cmd_len)
	{
		if (shell->cmd->curr_cmd[i] != NULL && ft_strchr(shell->cmd->curr_cmd[i], '>') != NULL)
		{
			if (shell->cmd->output != shell->cmd->temp_fd[1])
				close(shell->cmd->output);
			cmd_len = ms_args_len(shell->cmd->curr_cmd);
			if (ft_strncmp(shell->cmd->curr_cmd[i], ">>", 2) == 0)
				shell->cmd->output = open(shell->cmd->curr_cmd[i + 1],
						O_CREAT | O_APPEND | O_TRUNC, 00777);
			else
				shell->cmd->output = open(shell->cmd->curr_cmd[i + 1],
						O_WRONLY | O_CREAT, 00777);
			if (shell->cmd->output < 0)
				return (EXIT_FAILURE);
			error = ms_cmd_replace_out(shell, shell->cmd->curr_cmd);
			cmd_len = ms_args_len(shell->cmd->curr_cmd);
			i = -1;
		}
		i += 1;
	}
	if (error != EXIT_SUCCESS)
		return (error);
	return (EXIT_SUCCESS);
}

static int	ms_cmd_replace_in(t_shell *shell, char **cmd)
{
	char	**new_cmd;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 2;
	len = ms_args_len(cmd);
	new_cmd = ft_calloc(len - 1, sizeof(char *));
	if (new_cmd == NULL)
		return (ALLOCATION_PROBLEM_EXIT);
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
	ms_free_args(shell->cmd->curr_cmd);
	shell->cmd->curr_cmd = new_cmd;
	return (EXIT_SUCCESS);
}

static int	ms_cmd_replace_out(t_shell *shell, char **cmd)
{
	char	**new_cmd;
	int		i;
	int		j;
	int		flag;
	int		len;

	i = 0;
	j = 0;
	flag = 0;
	len = ms_args_len(cmd);
	new_cmd = ft_calloc(len, sizeof(char *));
	if (new_cmd == NULL)
		return (ALLOCATION_PROBLEM_EXIT);
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
	new_cmd[j] = NULL;
	ms_free_args(shell->cmd->curr_cmd);
	shell->cmd->curr_cmd = new_cmd;
	return (EXIT_SUCCESS);
}