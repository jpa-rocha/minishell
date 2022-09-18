/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:31:33 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/18 18:32:36 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

static int	check_lexer(t_shell *shell, int j)
{
	if (!shell->lexer[j])
		ms_free_args(shell->lexer);
	return (ALLOCATION_PROBLEM_EXIT);
}

static int	lexer_if_helper(t_shell *shell, int i)
{
	if ((shell->cmd->line[i] == PIPE
			&& check_char_in_quotes(shell->cmd->line, i, PIPE) == 0
			&& shell->cmd->line[i + 1] != '\0')
		|| shell->cmd->line[i] == '\0')
		return (0);
	return (1);
}

static char	**lexer_helper(t_shell *shell, int i, int j, int count)
{
	char	*temp;

	while (1)
	{
		if (lexer_if_helper(shell, i) == 0)
		{
			temp = ft_calloc(count + 1, sizeof(char));
			check_temp(temp, shell);
			ft_strlcpy(temp, &shell->cmd->line[i] - count, count + 1);
			shell->lexer[j] = ft_strtrim(temp, " ");
			free(temp);
			check_lexer(shell, j);
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
	return (shell->lexer);
}

int	ms_lexer(t_shell *shell)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	alloc_lexer(shell);
	shell->lexer = lexer_helper(shell, i, j, count);
	return (EXIT_SUCCESS);
}
