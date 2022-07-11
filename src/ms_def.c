/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_def.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 14:29:57 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/11 16:52:24 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_shell *ms_shell_init(char **env, char **argv)
{
	t_shell *shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (shell == NULL)
		return (NULL);
	shell->workenv = ms_env_create_work_env(env, argv);
	shell->env = ms_env_init_env(shell->workenv);
	shell->errnum = 0;
	return (shell);
}

t_cmd	*ms_cmd_init(char **env, char **argv)
{
	t_cmd	*cmd;

(void) env;
(void) argv;
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->symb = ft_calloc(1, sizeof(t_symbols));
	if (cmd->symb == NULL)
		return (NULL);
	//cmd->line = readline("minishell> ");
	cmd->builtin_num = 0;
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
	if (shell->workenv != NULL)
		ms_list_data_cleaner(shell->workenv);
	if (shell != NULL)
		free(shell);
	return (0);
}
