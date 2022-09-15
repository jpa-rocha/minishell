/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_def.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:29:57 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/15 11:17:56 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	ms_set_builtins(t_shell *shell);
static void	ms_update_shell_home(t_shell *shell);

t_shell	*ms_shell_init(char **env, char **argv, int shlvl)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (shell == NULL)
		return (NULL);
	shell->name = argv[0];
	shell->argv = argv;
	shell->shlvl = shlvl;
	shell->workenv = ms_env_create_work_env(shell, env);
	if (shell->workenv == NULL)
		ms_shell_cleanup(shell);
	shell->env = ms_env_init_env(shell);
	if (shell->env == NULL)
		ms_shell_cleanup(shell);
	ms_set_builtins(shell);
	shell->user = ms_env_ret_value(shell, "USER=");
	shell->home = ms_env_ret_value(shell, "HOME=");
	shell->status = 0;
	return (shell);
}

static void ms_set_builtins(t_shell *shell)
{
	shell->builtins[0] = "cd";
	shell->builtins[1] = "exit";
	shell->builtins[2] = "minishell";
	shell->builtins[3] = "export";
	shell->builtins[4] = "unset";
	shell->builtins[5] = "echo";
	shell->builtins[6] = "pwd";
	shell->builtins[7] = "env";
}
// CONTROLL NULL WHAT IF PATH IS NULL NEEDS TO BE FREED AT END?
char	**ms_cmd_path_creator(t_shell *shell)
{
	t_envvar	*line;
	t_node		*node;
	char		**path;

	path = NULL;
	node = ms_env_find_entry(shell->workenv, "PATH=");
	if (node == NULL)
	{
		path = ft_calloc(2, sizeof(char *));
		if (path == NULL)
			return (NULL);
		path[0] = ft_strdup(" ");
		path[1] = NULL;
	}
	else
	{
		line = (t_envvar *) node->data;
		if (line != NULL)
			path = ft_split(line->value, ':');
	}
	return (path);
}

t_cmd	*ms_cmd_init(t_shell *shell)
{
	t_cmd	*cmd;
	char	*prompt;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
	{
		shell->status = ALLOCATION_PROBLEM_EXIT;
		return (NULL);
	}
	cmd->path = ms_cmd_path_creator(shell);
	prompt = ms_prompt(shell);
	if (prompt == NULL)
		return (NULL);
	ms_update_shell_home(shell);
	cmd->cmd_idx = 0;
	cmd->changes_state = 0;
	cmd->line = readline(prompt);
	free(prompt);
	return (cmd);
}

static void	ms_update_shell_home(t_shell *shell)
{
	DIR		*dir;
	char	*home;

	home = ms_env_ret_value(shell, "HOME=");
	if (home != NULL && ft_strncmp(home, shell->home,
			ft_strlen(home) == 1))
	{
		dir = opendir(home);
		if (dir)
		{
			if (shell->home != NULL)
				free(shell->home);
			shell->home = ft_strdup(home);
			closedir(dir);
		}
		else if (ENOENT == errno)
			free(home);
	}
	if (home != NULL)
		free(home);
}
