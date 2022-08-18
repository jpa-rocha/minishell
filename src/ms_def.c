/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_def.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:29:57 by jrocha            #+#    #+#             */
/*   Updated: 2022/08/18 18:13:21 by mgulenay         ###   ########.fr       */
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
	shell->env = ms_env_init_env(shell);
	if (shell->env == NULL)
		ms_shell_cleanup(shell);
	shell->argv = argv;
	shell->exitcode = 0;
	return (shell);
}

// CONTROLL NULL WHAT IF PATH IS NULL NEEDS TO BE FREED AT END?
char	**ms_cmd_path_creator(t_shell *shell)
{
	t_envvar	*line;
	char		**path;

	path = NULL;
	line = (t_envvar *) ms_env_find_entry(shell->workenv, "PATH=");
	if (line != NULL)
		path = ft_split(line->value, ':');
	return (path);
}

t_cmd	*ms_cmd_init(t_shell *shell)
{
	t_cmd	*cmd;
	char	*prompt;

	cmd = ft_calloc(1, sizeof(t_cmd));
	//cmd = (t_cmd *)malloc((shell->cmd->n_cmd) * sizeof(t_cmd));
	if (cmd == NULL)
	{
		shell->exitcode = ALLOCATION_PROBLEM_EXIT;
		return (NULL);
	}
	// IS THIS BEING USED?? PATH GOES HERE
	cmd->path = ms_cmd_path_creator(shell);
	prompt = ms_prompt(shell);
	if (prompt == NULL)
		return (NULL);
	cmd->line = readline(prompt);
	free(prompt);
	shell->exitcode = EXIT_SUCCESS;
	return (cmd);
}

int	ms_cmd_cleanup(t_cmd *cmd)
{
	if (cmd->line != NULL)
		free(cmd->line);
	if (cmd->args != NULL)
		ms_free_args(cmd->args);
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
