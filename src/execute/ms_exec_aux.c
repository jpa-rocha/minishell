/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_aux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:42:44 by jrocha            #+#    #+#             */
/*   Updated: 2022/08/24 12:07:10 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_exec_here_doc_setup(t_shell *shell);
static int	ms_exec_set_input(t_shell *shell, char ***seq);
static int	ms_exec_set_output(t_shell *shell, char ***seq);

int	ms_exec_set_in_out(t_shell *shell, char ***seq)
{
	int	seq_len2;

	seq_len2 = ms_args_len(seq[shell->cmd->n_cmd]);
	if ((seq[0][0][0] == '<' && ft_strlen(seq[0][0]) == 1) || ft_strncmp(seq[0][1], "<<", 2))
		shell->exitcode = ms_exec_set_input(shell, seq);
	if ((seq[shell->cmd->n_cmd][seq_len2 - 2][0] == '>'
		&& ft_strlen(seq[shell->cmd->n_cmd][seq_len2 - 2]) == 1)
		|| ft_strncmp(seq[shell->cmd->n_cmd][seq_len2], "<<", 2))
		shell->exitcode = ms_exec_set_output(shell, seq);
	return (shell->exitcode);
}

int	ms_exec_here_doc(t_shell *shell)
{
	char	*line;
	int		len;

	if(ms_exec_here_doc_setup(shell) != 0)
		return (EXIT_FAILURE);
	while (1)
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
	if (line != NULL)
		free(line);
	close(shell->cmd->input);
	return (EXIT_SUCCESS);
}

static int	ms_exec_set_input(t_shell *shell, char ***seq)
{
	shell->cmd->input = open(seq[0][1], O_RDONLY);
	if (shell->cmd->input < 0)
		return (7);
	if (ft_strncmp(seq[0][1], "<<", 2) == 0)
	{
		if (ms_exec_here_doc(shell) != 0)
			return (EXIT_FAILURE);
	}
	if (dup2(shell->cmd->input, STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	shell->cmd->rdir_idx = 2;
	return (EXIT_SUCCESS);
}

static int	ms_exec_set_output(t_shell *shell, char ***seq)
{
	int	seq_len2;

	seq_len2 = ms_args_len(seq[shell->cmd->n_cmd - 1]);
	if (seq[shell->cmd->n_cmd][seq_len2 - 2][0] == '>')
		shell->cmd->output = open(seq[shell->cmd->n_cmd][seq_len2 - 1], O_CREAT
				| O_RDWR | O_TRUNC, 00777);
	else
		shell->cmd->output = open(seq[shell->cmd->n_cmd][seq_len2 - 1], O_WRONLY
				| O_APPEND | O_CREAT, 00777);
	if (shell->cmd->output < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	ms_exec_here_doc_setup(t_shell *shell)
{
	shell->cmd->heredoc = 1;
	shell->cmd->input = open("heredoc_aux.txt", O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (shell->cmd->input < 0)
		return (EXIT_FAILURE);
	shell->cmd->limiter = shell->cmd->seq[0][2];
	return (0);
}
