/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_def.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:29:57 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/13 10:15:34 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_shell	*ms_shell_init(char **env, char **argv)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (shell == NULL)
		return (NULL);
	shell->name = argv[0];
	shell->workenv = ms_env_create_work_env(shell, env);
	if (shell->workenv == NULL)
		ms_shell_cleanup(shell);
	shell->env = ms_env_init_env(shell->workenv);
	if (shell->env == NULL)
		ms_shell_cleanup(shell);
	shell->path = ms_shell_path_creator(shell);
	if (shell->path == NULL)
		ms_shell_cleanup(shell);
	shell->argv = argv;
	shell->exitcode = 0;
	return (shell);
}

// CONTROLL NULL
char	**ms_shell_path_creator(t_shell *shell)
{
	t_node		*node;
	t_envvar	*line;
	char		**path;

	if (shell->path != NULL)
		ms_free_args(shell->path);
	path = NULL;
	node = ms_env_find_entry(shell->workenv, "PATH=");
	if (node != NULL)
	{
		line = (t_envvar *) node->data;
		path = ft_split(line->value, ':');
	}
	return (path);
}

t_cmd	*ms_cmd_init(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
	{
		shell->exitcode = ALLOCATION_PROBLEM_EXIT;
		return (NULL);
	}
	cmd->symb = ft_calloc(1, sizeof(t_symbols));
	if (cmd->symb == NULL)
	{
		shell->exitcode = ALLOCATION_PROBLEM_EXIT;
		free(cmd);
		return (NULL);
	}
	cmd->line = readline("minishell> ");
	cmd->builtin_num = 0;
	shell->exitcode = 0;
	return (cmd);
}

int	ms_cmd_cleanup(t_cmd *cmd)
{
	//int	errnum;

	//errnum = cmd->errnum;
	if (cmd->symb != NULL)
		free(cmd->symb);
	if (cmd->line != NULL)
		free(cmd->line);
	if (cmd->args != NULL)
		ms_free_args(cmd->args);
	free(cmd);
	return (0);
}

int	ms_shell_cleanup(t_shell *shell)
{
	if (shell->cmd != NULL)
		ms_cmd_cleanup(shell->cmd);
	if (shell->env != NULL)
		ms_free_args(shell->env);
	if (shell->path != NULL)
		ms_free_args(shell->path);
	if (shell->workenv != NULL)
	{
		ms_list_data_cleaner(shell->workenv);
		list_destroyer(shell->workenv);
	}
	if (shell != NULL)
		free(shell);
	return (0);
}
