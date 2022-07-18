/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:31:33 by mgulenay          #+#    #+#             */
/*   Updated: 2022/07/18 21:54:14 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	check_quotes(t_cmd *cmd)
{
	int	i;
	int	quote_end;

	i = 0;
	while (cmd->line[i])
	{
		if (cmd->line[i] == SQ || cmd->line[i] == DQ)
		{
			quote_end = i + 1;
			while (cmd->line[i] && (cmd->line[quote_end] != cmd->line[i]))
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
		i++;
	}
	return (0);
}

/* check how many group of commands we have - - the separator is the pipe */
/* aa | f | , this is ok, cmd nmb is 2; 
	but here: aa | f | | , cmd num is 3, need to fix 
*/
int	get_nmb_cmd(t_cmd *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (cmd->line[i])
	{
		if (cmd->line[i] == PIPE)
		{
			i += 1;
			while (cmd->line[i] == ' ')
				i += 1;
			if (cmd->line[i])
				count += 1;
		}
		i += 1;
	}
	return (count);
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

void	alloc_lexer(t_shell *shell)
{
	shell->cmd->n_cmd = get_nmb_cmd(shell->cmd);
	shell->lexer = ft_calloc(shell->cmd->n_cmd + 1, sizeof(char *));
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
	if (check_quotes(shell->cmd))
		printf("err");
	alloc_lexer(shell);
	while (1)
	{
		if (shell->cmd->line[i] == PIPE || shell->cmd->line[i] == '\0')
		{
			temp = ft_calloc(count + 2, sizeof(char));
			check_temp(temp, shell);
			ft_strlcpy(temp, &shell->cmd->line[i] - count, count + 1);
			shell->lexer[j] = ft_strtrim(temp, " ");
			if (!shell->lexer[j])
				check_lexer(shell);
			printf("%s\n", shell->lexer[j]);
			free(temp);
			j += 1;
			if (shell->cmd->line[i] == '\0')
				break ;
			i += 1;
			count = 0;
		}
		count += 1;
		i += 1;
	}
	//shell->lexer[j] = NULL;
	return (EXIT_SUCCESS);
}

/*  int	check_quotes(t_shell *shell)
{
	int	i;
	int	j;
	int	quote_end;
	char	c;

	i = 0;
	j = 0;
	while (j < shell->cmd->n_cmd)
	{
		while (shell->lexer[j][i])
		{
			if (shell->lexer[j][i] == SQ || shell->lexer[j][i] == DQ)
			{
				c = shell->lexer[j][i];
				quote_end = i + 1;
				while (shell->lexer[j][i] && shell->lexer[j][quote_end] != c)
				{
					quote_end++;
				}
				if (shell->lexer[j][quote_end] == '\0')
				{
					perror("not closing quotes\n");
					break ;
				}
			}
			i++;
		}
		j++;
	}
	return (0);
} */
