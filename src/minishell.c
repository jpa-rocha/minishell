/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:41:05 by jrocha            #+#    #+#             */
/*   Updated: 2022/08/25 22:11:32 by mgulenay         ###   ########.fr       */
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
	ms_signals();
	while (1)
	{
		shell->cmd = ms_cmd_init(shell);
		 if (shell->cmd == NULL)
			ms_error_management(shell);
		if (shell->exitcode == EXIT_SUCCESS)
		{
			if (shell->cmd->line == NULL)
				break ;
			if (ms_parser(shell) != EXIT_SUCCESS)
				return (ms_error_management(shell));
			add_history(shell->cmd->line);
			shell->exitcode = ms_exec(shell);
			ms_cmd_cleanup(shell->cmd);
			ms_free_args(shell->lexer);
		}
	}
	write(1, "exit\n", 5);
	return (ms_shell_cleanup(shell));
}
