/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:57:44 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/16 11:28:14 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_exec_here_doc_setup(t_shell *shell);
static int	ms_here_doc_end(t_shell *shell, char *line);

int	ms_exec_here_doc(t_shell *shell)
{
	char	*line;
	int		len;

	if (ms_exec_here_doc_setup(shell) != 0)
		return (EXIT_FAILURE);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			ft_printf(STDERR_FILENO, HEREDOC_MSG, shell->cmd->limiter);
			break ;
		}
		len = ft_strlen(line);
		if (len == 1 && ft_strncmp(line, "\n", 1) != 0)
			len = 2;
		if (ft_strncmp(line, shell->cmd->limiter, len - 1) == 0
			&& ft_strlen(line) - 1 == ft_strlen(shell->cmd->limiter))
			break ;
		write(shell->cmd->input, line, ft_strlen(line));
		free(line);
	}
	return (ms_here_doc_end(shell, line));
}

static int	ms_exec_here_doc_setup(t_shell *shell)
{
	shell->cmd->heredoc = 1;
	shell->cmd->input = open("heredoc_aux.txt",
			O_CREAT | O_RDWR | O_TRUNC, 00777);
	if (shell->cmd->input < 0)
		return (EXIT_FAILURE);
	shell->cmd->limiter = shell->cmd->curr_cmd[1];
	return (EXIT_SUCCESS);
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
