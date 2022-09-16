/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:53:56 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/16 14:03:37 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* ERROR CHECKS AT THE BEGINNING */
/* checks whether quotes are closed */
static int	check_quotes(t_cmd *cmd)
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
					printf("quotes are not closed\n");
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

/* redirections are properly used */
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
static int	check_redirections(t_cmd *cmd)
{
	int	i;
	int	c;

	i = 0;
	c = counter_io(cmd);
	while (cmd->line[i] == ' ')
		i++;
	while (cmd->line[i] != '\0' && (cmd->line[i] == SM || cmd->line[i] == GR))
	{
		if ((cmd->line[i] == SM && c < 4 && cmd->line[i + 1] != ' ')
			|| (cmd->line[i] == GR && c < 4 && cmd->line[i + 1] != ' ')
			|| (cmd->line[i] == SM && cmd->line[i + 1] == GR))
		{
			printf(ERR_MU, "newline");
			return (EXIT_FAILURE);
		}
		else if (cmd->line[i] == SM && c > 2 && cmd->line[i + 1] == ' ')
		{
			printf(ERR_MU, "<");
			return (EXIT_FAILURE);
		}
		else if (cmd->line[i] == SM && c > 2)
		{
			printf(ERR_MU, "<<");
			return (EXIT_FAILURE);
		}
		else if (cmd->line[i] == GR && c > 2 && cmd->line[i + 1] == ' ')
		{
			printf(ERR_MU, ">");
			return (EXIT_FAILURE);
		}
		else if (cmd->line[i] == GR && c > 2)
		{
			printf(ERR_MU, ">>");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/* error check for cases like
	 /, //, /. etc. 
*/
/* static int	check_slash(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->line[i] != '\0' && (cmd->line[i] == SLASH || cmd->line[i] == BSLASH || 
		cmd->line[i] == '-'))
	{
		if (cmd->line[i] == SLASH)
		{
			printf(ERR_ISDIR, &cmd->line[i++]);
			return (EXIT_FAILURE);
		}
		else if (cmd->line[i] == BSLASH || cmd->line[i] == '-')
		{
			printf(ERR_NF, &cmd->line[i++]);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
} */

int	check_char_errors(t_shell *shell, t_cmd *cmd)
{
	if (check_quotes(cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_redirections(cmd))
		return (EXIT_FAILURE);
/* 	if (check_slash(cmd))
		return (EXIT_FAILURE); */
	if (check_empty_pipes(cmd))
		return (EXIT_FAILURE);
	if (check_pipes(cmd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
