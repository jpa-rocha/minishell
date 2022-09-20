/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:53:56 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/20 16:53:22 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* ERROR CHECKS AT THE BEGINNING */
/* checks whether quotes are closed */
int	check_quotes(t_cmd *cmd)
{
	int	i;
	int	quote_end;

	i = 0;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == SQ || cmd->line[i] == DQ)
		{
			quote_end = i + 1;
			while (cmd->line[i] && (cmd->line[quote_end] != cmd->line[i]))
			{
				if (!cmd->line[quote_end])
				{
					cmd->builtin_num = -2;
					return (EXIT_FAILURE);
				}
				quote_end++;
			}
			i = quote_end;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/* counts redirections */
static int	counter_io(t_cmd *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == SM)
			count++;
		else if (cmd->line[i] == GR)
			count++;
		i++;
	}
	return (count);
}

/* Error check for cases like: < , > , <<, >>, <> and
	>>>>>, <<<<<<, > > > >, >> >> >> >> etc.
*/
static int	redirections_helper(t_cmd *cmd, int c, int i)
{
	if (cmd->line[i] == SM && c > 2 && cmd->line[i + 1] == ' ')
	{
		cmd->builtin_num = -6;
		return (EXIT_FAILURE);
	}
	else if (cmd->line[i] == SM && c > 2)
	{
		cmd->builtin_num = -7;
		return (EXIT_FAILURE);
	}
	else if (cmd->line[i] == GR && c > 2 && cmd->line[i + 1] == ' ')
	{
		cmd->builtin_num = -8;
		return (EXIT_FAILURE);
	}
	else if (cmd->line[i] == GR && c > 2)
	{
		cmd->builtin_num = -9;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_redirections(t_cmd *cmd)
{
	int	i;
	int	c;
	int	len;

	i = 0;
	len = ft_strlen(cmd->line);
	c = counter_io(cmd);
	while (cmd->line[i] == ' ')
		i++;
	while (cmd->line[i] != '\0' && (cmd->line[i] == SM || cmd->line[i] == GR))
	{
		if (len == 1 && (cmd->line[i] == SM || (cmd->line[i] == GR)))
			cmd->builtin_num = -5;
		else if (len == 2 && (ft_strncmp(cmd->line, ">>", len)
				|| ft_strncmp(cmd->line, "<<", len)
				|| ft_strncmp(cmd->line, "<>", len)))
			cmd->builtin_num = -5;
		else if (redirections_helper(cmd, c, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	check_slash(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->line[i] != '\0' && (cmd->line[i] == SLASH
			|| cmd->line[i] == BSLASH || cmd->line[i] == '-'))
	{
		if (cmd->line[i] == SLASH)
		{
			cmd->builtin_num = -12;
			cmd->error_inc = i;
			return (EXIT_FAILURE);
		}
		else if (cmd->line[i] == BSLASH || cmd->line[i] == '-')
		{
			cmd->builtin_num = -13;
			cmd->error_inc = i;
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
