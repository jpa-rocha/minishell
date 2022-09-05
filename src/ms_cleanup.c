/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:31:35 by jrocha            #+#    #+#             */
/*   Updated: 2022/08/25 22:11:05 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	ms_free_seq(t_cmd *cmd)
{
	while (cmd->n_cmd - 1 >= 0)
	{
		ms_free_args(cmd->seq[cmd->n_cmd]);
		cmd->n_cmd =- 1;
	}
	free(cmd->seq);
}

void	ms_free_args(char **args)
{
	int	i;

	i = ms_args_len(args) -1;
	while (i >= 0)
	{
		if (args[i] != NULL)
			free(args[i]);
		i -= 1;
	}
	free(args);
}

int	ms_cmd_cleanup(t_cmd *cmd)
{
	if (cmd->line != NULL)
		free(cmd->line);
	if (cmd->seq != NULL)
		ms_free_seq(cmd);
	if (cmd->path != NULL)
		ms_free_args(cmd->path);
	free(cmd);
	return (EXIT_SUCCESS);
}

int	ms_shell_cleanup(t_shell *shell)
{
	if (shell->cmd != NULL)
		ms_cmd_cleanup(shell->cmd);
	if (shell->env != NULL)
		ms_free_args(shell->env);
	if (shell->workenv != NULL)
	{
		ms_list_data_cleaner(shell->workenv);
		list_destroyer(shell->workenv);
	}
	if (shell != NULL)
		free(shell);
	return (EXIT_SUCCESS);
}
