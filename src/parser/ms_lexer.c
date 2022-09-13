/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:31:33 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/13 10:55:18 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	check_lexer(t_shell *shell);
static int	check_temp(char *temp, t_shell *shell);

/* check how many group of commands we have - - the separator is the pipe */
int	get_nmb_cmd(t_cmd *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == PIPE && check_pipe_in_quotes(cmd->line) == 0)
		{
			i += 1;
			while (cmd->line[i] == ' ' || cmd->line[i] == PIPE)
				i += 1;
			if (cmd->line[i] != '\0')
				count += 1;
			if (cmd->line[i] == '\0')
			{
				printf("pipe needs an argument\n");
				return (EXIT_FAILURE);
			}
		}
		i += 1;
	}
	return (count);
}

void	alloc_lexer(t_shell *shell)
{
	shell->cmd->n_cmd = get_nmb_cmd(shell->cmd);
	shell->lexer = ft_calloc(shell->cmd->n_cmd + 1, sizeof(char *));
}

static int	check_temp(char *temp, t_shell *shell)
{
	if (!temp)
	{
		free(temp);
		ms_free_args(shell->lexer);
		return (ALLOCATION_PROBLEM_EXIT);
	}
	return (0);
}

static int	check_lexer(t_shell *shell)
{
	ms_free_args(shell->lexer);
	return (ALLOCATION_PROBLEM_EXIT);
}

int	ms_lexer(t_shell *shell)
{
	int		i;
	int		j;
	int		count;
	char	*temp;

	i = 0;
	j = 0;
	count = 0;
	alloc_lexer(shell);
	while (1)
	{
		if ((shell->cmd->line[i] == PIPE && check_pipe_in_quotes(shell->cmd->line) == 0 && 
			shell->cmd->line[i + 1] != '\0') || shell->cmd->line[i] == '\0')
		{
			temp = ft_calloc(count + 1, sizeof(char));
			check_temp(temp, shell);
			ft_strlcpy(temp, &shell->cmd->line[i] - count, count + 1);
			shell->lexer[j] = ft_strtrim(temp, " ");
			//shell->lexer[j] = ft_strdup(temp);
			free(temp);
			if (!shell->lexer[j])
				check_lexer(shell);
			j += 1;
			if (shell->cmd->line[i] == '\0')
				break ;
			i += 1;
			count = 0;
		}
		count += 1;
		i += 1;
	}
	shell->lexer[j] = NULL;
	return (EXIT_SUCCESS);
}
