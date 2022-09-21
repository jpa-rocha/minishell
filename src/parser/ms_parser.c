/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:05:45 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/21 11:00:22 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	free_r_quotes(char *str, char *temp)
{
	if (str != NULL)
		free(str);
	if (str != NULL)
		free(temp);
}

static char	*remove_quotes_helper(char *str, char *temp, int index, int quote)
{
	int		k;

	k = index;
	while (str[index] != '\0')
	{
		if (str[index] == quote)
		{
			if (str[index + 1] == quote)
				return (ft_strjoin(temp, &str[index + 2]));
			index += 1;
			while (str[index] != '\0')
			{
				if (str[index] != quote)
				{
					temp[k] = str[index];
					k += 1;
				}
				index += 1;
			}
			return (ft_strdup(temp));
		}
	}
	return (NULL);
}

int	ms_parser(t_shell *shell)
{
	if (shell->cmd->line != NULL)
	{
		if (check_char_errors(shell->cmd) == EXIT_FAILURE)
		{
			shell->status = -2;
			shell->cmd->n_cmd = 1;
			return (EXIT_SUCCESS);
		}
		ms_lexer(shell);
	}
	shell->cmd->seq = create_seq_from_lexer(shell);
	if (shell->cmd->seq == NULL)
	{
		shell->status = ALLOCATION_PROBLEM_EXIT;
		return (shell->status);
	}
	ms_free_args(shell->lexer);
	shell->lexer = NULL;
	return (EXIT_SUCCESS);
}

char	*remove_quotes(char *str, int index, int quote)
{
	char	*temp;
	char	*ret;

	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	ft_strlcpy(temp, str, index + 1);
	ret = remove_quotes_helper(str, temp, index, quote);
	free_r_quotes(str, temp);
	return (ret);
}
