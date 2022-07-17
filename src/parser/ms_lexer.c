/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:31:33 by mgulenay          #+#    #+#             */
/*   Updated: 2022/07/17 21:23:58 by mgulenay         ###   ########.fr       */
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

void	ms_lexer(t_cmd *cmd)
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
	
}

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
