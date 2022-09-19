/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 08:47:57 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/19 09:02:22 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* checks how many group of substrings we have -- the separator is the PIPE */
int	get_nmb_cmd(t_cmd *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (cmd->line[i] != '\0')
	{
		if (cmd->line[i] == PIPE
			&& check_char_in_quotes(cmd->line, i, PIPE) == 0)
		{
			i += 1;
			while (cmd->line[i] == ' ' || cmd->line[i] == PIPE)
				i += 1;
			if (cmd->line[i] != '\0')
				count += 1;
			if (cmd->line[i] == '\0')
			{
				cmd->builtin_num = -10;
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

/* removes white spaces in case they are not inside the quotes */
char	*remove_white_spaces(char *str)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i] != '\0')
	{
		if ((str[i] == ' ' && str[i + 1] == ' ') != 0
			&& check_char_in_quotes(str, i, ' ') == 0)
		{
			i++;
			continue ;
		}
		new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	str = ft_strdup(new_str);
	free(new_str);
	return (str);
}
