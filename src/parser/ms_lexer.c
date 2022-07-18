/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:31:33 by mgulenay          #+#    #+#             */
/*   Updated: 2022/07/18 13:16:12 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* check how many group of commands we have - - our separetor is
the pipe itself ; look for the closing
quotes; if not print error message; if there is continue */

int	n_commands(t_cmd *cmd)
{
	int	i;
	int	quote_end;
	int	count;

	i = 0;
	quote_end = 0;
	count = 1;

	while (cmd->line[i])
	{
		if (cmd->line[i] == '"' ||cmd->line[i] == '\'')
		{
			quote_end = i + 1;
			while (cmd->line[quote_end] != cmd->line[i] && cmd->line[i])
			{
				if (!cmd->line[quote_end])
				{
					perror("not closing quotes\n");
					break ;
				}
				quote_end++;
			}
			i = quote_end;
		}
		else if (cmd->line[i] == '|')
		{
			i++;
			while (cmd->line[i] == ' ')
				i++;
			if (cmd->line[i])
				count++;
		}
		i++;
	}
	return (count);
}

int ms_lexer(t_shell *shell)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	shell->cmd->n_cmd = n_commands(shell->cmd);
	shell->lexer = ft_calloc(shell->cmd->n_cmd + 1, sizeof(char *));

	while (1)
	{
		if (shell->cmd->line[i] == '|' || shell->cmd->line[i] == '\0')
		{
			shell->lexer[j] = ft_calloc(count + 2, sizeof(char));
			if (!shell->lexer[j])
			{
				ms_free_args(shell->lexer);
				return (ALLOCATION_PROBLEM_EXIT);
			}
			ft_strlcpy(shell->lexer[j], &shell->cmd->line[i] - count , count + 1);
			printf("%s\n", shell->lexer[j]);
			j += 1;
			if (shell->cmd->line[i] == '\0')
				break;
			i += 1;
			count = 0;
		}
		count += 1;
		i += 1;
	}
	shell->lexer[j] = NULL;
	return (EXIT_SUCCESS);
}

/* void	ms_lexer(t_cmd *cmd)
{
	int	i;
	int	j;
	int	start;
	int	end;

	i = 0;
	j = 0;
	start = 0;
	end = 0;
	while (cmd->line[start])
		start++;
	while (cmd->line[i])
	{
		if (cmd->line[i] == '"' ||cmd->line[i] == '\'')
		{
			end = i + 1;
			while (cmd->line[end] != cmd->line[i] && cmd->line[i])
			{
				if (!cmd->line[end])
				{
					perror("not closing quotes\n");
					break ;
				}
				end++;
			}
			i = end;
		}
		else if (cmd->line[i] == '|')
		{
		
		i++;
	}
	end = i;
	
} */

/* int	ms_check_pipe(t_cmd *cmd)
{
	//char	**split;
	int		i;

	i = 0;
	cmd->args = ft_split(cmd->line, '|');
	while (cmd->args[i])
	{
			printf("%s\n", cmd->args[i]);
		i++;
	}
	return (0);
} */
