/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:41:05 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/13 10:49:30 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// Entry point for the minishell logic

int	main(int argc, char **argv, char **env)
{
	int	exitcode;

	if (argc > 1 || !argv[0])
	{
		printf("%s", ERR_ARG);
		return (1);
	}
	exitcode = ms_shell(env, argv);
	return (exitcode);
}

// Entry point for the minishell logic
int	ms_shell(char **env, char **argv)
{
	t_shell	*shell;

	shell = ms_shell_init(env, argv);
	if (shell == NULL)
		return (ms_error_management(shell));
	ms_logo();
	ms_signals_parent();
	while (1)
	{
		shell->cmd = ms_cmd_init(shell);
		if (shell->cmd == NULL)
			ms_error_management(shell);
		if (shell->exitcode == EXIT_SUCCESS)
		{
			if (shell->cmd->line == NULL)
				break ;
			if (ms_parser(shell) == EXIT_SUCCESS)
			{
				add_history(shell->cmd->line);
				shell->exitcode = ms_exec(shell);
				ms_cmd_cleanup(shell->cmd);
			}
			else
				ms_error_management(shell);
		}
	}
	write(1, "exit\n", 5);
	return (ms_shell_cleanup(shell));
}
