/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_def.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:29:57 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/08 13:44:40 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_cmd	*ms_cmd_init(char **env, char **argv)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->symb = ft_calloc(1, sizeof(t_symbols));
	if (cmd->symb == NULL)
	{
		cmd->errnum = 2;
		return (cmd);
	}
	cmd->line = readline("minishell> ");
	cmd->env = ms_create_env(env, argv);
	cmd->errnum = 0;
	return (cmd);
}

int	ms_cmd_cleanup(t_cmd *cmd)
{
	int	errnum;

	errnum = cmd->errnum;
	if (cmd->symb != NULL)
		free(cmd->symb);
	if (cmd->line != NULL)
		free(cmd->line);
	if (cmd->args != NULL)
		ms_free_args(cmd->args);
	if (cmd->env != NULL)
		ms_free_args(cmd->env);
	free(cmd);
	return (errnum);
}

void	ms_free_args(char **args)
{
	int	i;

	i = ms_args_len(args);
	while (i >= 0)
	{
		free(args[i]);
		i -= 1;
	}
	free(args);
}

int	ms_args_len(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i += 1;
	return (i);
}
