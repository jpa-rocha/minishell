/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:41:05 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/13 11:23:41 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// Entry point for the minishell logic
int g_exit;

int	main(int argc, char **argv, char **env)
{
	int	error;

	error = 0;
	if (argc > 1 || !argv[0])
	{
		printf("%s", ERR_ARG);
		return (1);
	}
	error = ms_shell(env, argv, 1);
	return (error);
}

// Entry point for the minishell logic
int	ms_shell(char **env, char **argv, int shlvl)
{
	t_shell	*shell;

	shell = ms_shell_init(env, argv, shlvl);
	if (shell == NULL)
		return (ms_error_management(shell));
	ms_logo();
	ms_signals();
	while (1)
	{
		shell->cmd = ms_cmd_init(shell);
		if (shell->cmd == NULL)
			ms_error_management(shell);
		if (shell->cmd != NULL)
		{
			if (shell->cmd->line == NULL)
				break ;
			if (ms_parser(shell) == EXIT_SUCCESS)
			{
				add_history(shell->cmd->line);
				shell->status = ms_exec(shell);
				ms_cmd_cleanup(shell->cmd);
			}
			else
				ms_error_management(shell);
		}
	}
	write(1, "exit\n", 5);
	return (ms_shell_cleanup(shell));
}
