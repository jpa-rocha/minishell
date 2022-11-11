/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:57:44 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/22 09:32:25 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_exec_here_doc_setup(t_shell *shell, int i);
static int	ms_here_doc_end(t_shell *shell, char *line, int ret);
static int	ms_exec_here_doc(t_shell *shell, int i);
static void	ms_here_doc_waiting(t_shell *shell);

int	ms_exec_here_doc_fork(t_shell *shell, int i)
{
	ms_signals_block();
	shell->pid = fork();
	if (shell->pid == 0)
	{
		ms_signals_heredoc();
		if (ms_exec_here_doc(shell, i) == 0)
			exit(0);
		else
			exit(5);
	}
	else
	{
		ms_here_doc_waiting(shell);
		if (shell->cmd->input < 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	ms_here_doc_waiting(t_shell *shell)
{
	waitpid(shell->pid, &shell->status, 0);
	ms_signals_parent();
	shell->cmd->heredoc = 1;
	if (ms_args_len(shell->cmd->curr_cmd) < 3)
		shell->cmd->builtin_num = -14;
	if (WIFSIGNALED(shell->status) == 1)
		shell->status = 128 + WTERMSIG(shell->status);
	else
		shell->status = WEXITSTATUS(shell->status);
	if (shell->status == 130)
	{
		ft_printf(STDIN_FILENO, "\n");
		shell->cmd->builtin_num = -15;
	}
	if (shell->status == 5)
		shell->cmd->builtin_num = -5;
	shell->cmd->input = open("heredoc_aux.txt", O_RDONLY);
}

static int	ms_exec_here_doc(t_shell *shell, int i)
{
	char	*line;
	int		len;

	if (ms_exec_here_doc_setup(shell, i) != 0)
		return (EXIT_FAILURE);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			ft_printf(STDERR_FILENO, HEREDOC_MSG, shell->cmd->limiter);
			return (ms_here_doc_end(shell, line, EXIT_SUCCESS));
		}
		len = ft_strlen(line);
		if (len == 1 && ft_strncmp(line, "\n", 1) != 0)
			len = 2;
		if (ft_strncmp(line, shell->cmd->limiter, len - 1) == 0
			&& ft_strlen(line) - 1 == ft_strlen(shell->cmd->limiter))
			break ;
		line = (char *) ms_dollar_check(shell, line);
		write(shell->cmd->input, line, ft_strlen(line));
		free(line);
	}
	return (ms_here_doc_end(shell, line, EXIT_SUCCESS));
}

static int	ms_exec_here_doc_setup(t_shell *shell, int i)
{
	close(shell->cmd->temp_fd[0]);
	close(shell->cmd->temp_fd[1]);
	shell->cmd->input = open("heredoc_aux.txt",
			O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (shell->cmd->input < 0)
		return (EXIT_FAILURE);
	shell->cmd->limiter = shell->cmd->curr_cmd[i + 1];
	if (shell->cmd->limiter == NULL)
	{
		shell->cmd->builtin_num = -5;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	ms_here_doc_end(t_shell *shell, char *line, int ret)
{
	if (line != NULL)
		free(line);
	close(shell->cmd->input);
	close(shell->cmd->temp_fd[0]);
	close(shell->cmd->temp_fd[1]);
	return (ret);
}
