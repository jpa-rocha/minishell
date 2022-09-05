/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:42:44 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/05 14:34:36 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_cmd_replace(t_shell *shell, char **cmd);
static int	ms_exec_here_doc_setup(t_shell *shell);
static int	ms_exec_set_input(t_shell *shell, char **cmd);
static int	ms_exec_set_output(t_shell *shell, char **cmd);
static int	ms_here_doc_end(t_shell *shell, char *line);

// WHAT IF COMMANDS ARE IN WRONG ORDER? WRONG NUMBER
int	ms_exec_set_in_out(t_shell *shell, char **cmd)
{
	int	cmd_len;

	cmd_len = ms_args_len(cmd);
	if ((cmd[0][0] == '<' && ft_strlen(cmd[0]) == 1)
		|| ft_strncmp(cmd[0], "<<", 2) == 0)
		shell->exitcode = ms_exec_set_input(shell, cmd);
	cmd_len = ms_args_len(shell->cmd->curr_cmd);
	if (cmd_len >= 3 && cmd[cmd_len - 2][0] == '>'
		&& (ft_strlen(cmd[cmd_len - 2]) == 1
		|| ft_strncmp(cmd[cmd_len], ">>", 2) == 0))
		shell->exitcode = ms_exec_set_output(shell, cmd);
	else
	{
		shell->cmd->input = shell->cmd->temp_fd[0];
		shell->cmd->output = shell->cmd->temp_fd[1];
	}
	return (shell->exitcode);
}

int	ms_exec_here_doc(t_shell *shell)
{
	char	*line;
	int		len;

	if (ms_exec_here_doc_setup(shell) != 0)
		return (EXIT_FAILURE);
	while (line != NULL)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO, 0);
		len = ft_strlen(line);
		if (len == 1 && ft_strncmp(line, "\n", 1) != 0)
			len = 2;
		if (ft_strncmp(line, shell->cmd->limiter, len - 1) == 0)
		{
			free(line);
			line = get_next_line(STDIN_FILENO, 1);
			break ;
		}
		write(shell->cmd->input, line, ft_strlen(line));
		free(line);
	}
	return (ms_here_doc_end(shell, line));
}

static int	ms_here_doc_end(t_shell *shell, char *line)
{
	if (line != NULL)
		free(line);
	close(shell->cmd->input);
	shell->cmd->input = open("heredoc_aux.txt", O_RDONLY);
	if (shell->cmd->input < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ms_exec_set_input(t_shell *shell, char **cmd)
{
	if (ft_strncmp(cmd[0], "<<", 2) == 0)
	{
		if (ms_exec_here_doc(shell) != 0)
			return (EXIT_FAILURE);
	}
	else
		shell->cmd->input = open(cmd[1], O_RDONLY);
	if (shell->cmd->input < 0)
		return (EXIT_FAILURE);
	if (dup2(shell->cmd->input, STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	shell->exitcode = ms_cmd_replace(shell, cmd);
	return (EXIT_SUCCESS);
}

static int	ms_cmd_replace(t_shell *shell, char **cmd)
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

// TODO -> REMOVE OUTPUT SYMBOLS AND FILE NAME - CREATE NEW CMD
// change order of conditions
static int	ms_exec_set_output(t_shell *shell, char **cmd)
{
	int	cmd_len;

	cmd_len = ms_args_len(cmd);
	if (ft_strncmp(cmd[cmd_len - 2], ">>", 2) == 0)
		shell->cmd->output = open(cmd[cmd_len - 1]
				, O_CREAT | O_APPEND | O_TRUNC, 00777);
	else
		shell->cmd->output = open(cmd[cmd_len - 1]
				, O_WRONLY | O_RDWR | O_CREAT, 00777);
	if (shell->cmd->output < 0)
		return (EXIT_FAILURE);
	shell->exitcode = ms_cmd_replace(shell, cmd);
	return (EXIT_SUCCESS);
}

static int	ms_exec_here_doc_setup(t_shell *shell)
{
	shell->cmd->heredoc = 1;
	shell->cmd->input = open("heredoc_aux.txt"
			, O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (shell->cmd->input < 0)
		return (EXIT_FAILURE);
	shell->cmd->limiter = shell->cmd->curr_cmd[1];
	return (EXIT_SUCCESS);
}
