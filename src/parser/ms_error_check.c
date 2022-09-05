/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:53:56 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/02 15:27:54 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* ERROR CHECKS AT THE BEGINNING */
/* checks whether quotes are closed */
int	check_quotes(char *str)
{
	int	i;
	int	quote_end;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == SQ || str[i] == DQ)
		{
			quote_end = i + 1;
			while (str[i] && (str[quote_end] != str[i]))
			{
				if (!str[quote_end])
				{
					perror("not closing quotes\n");
					return (1);
				}
				quote_end++;
			}
			i = quote_end;
		}
		i++;
	}
	return (0);
}

/* redirections are properly used */
int	counter_io(t_cmd *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd->line[i])
	{
		if (cmd->line[i] == SM)
			count++;
		else if (cmd->line[i] == GR)
			count++;
		i++;
	}
	return (count);
}

/* Exit code needs to be 2 , perror returns already errnum ? */
/* Error check for cases like: 
	< , > , <<, >>, <> and
	>>>>>, <<<<<<, > > > >, >> >> >> >> etc.
*/
int	check_only_io(t_cmd *cmd)
{
	int	i;
	int	c;

	i = 0;
	c = counter_io(cmd);
	while (cmd->line[i] == ' ')
		i++;
	while (cmd->line[i] != '\0')
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
/*	exit status for Slash is 126 ;
	exit status for Back Slash is 127 */
int	check_slash(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->line[i] != '\0')
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
}

int	check_char_errors(t_cmd *cmd)
{
	if (check_quotes(cmd->line))
		return (EXIT_FAILURE);
	if (check_only_io(cmd))
		return (EXIT_FAILURE);
	if (check_slash(cmd))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
