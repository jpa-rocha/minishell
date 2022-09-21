/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:41:05 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/21 19:28:04 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	ms_shell_main_loop(t_shell	*shell);

// Entry point for the minishell logic
int	main(int argc, char **argv, char **env)
{
	int	error;

	error = 0;
	if (argc > 1 || !argv[0])
	{
		printf("%s", ERR_ARG);
		return (1);
	}
	error = ms_shell(env, argv, 0);
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
	ms_signals_parent();
	ms_shell_main_loop(shell);
	write(1, "exit\n", 5);
	return (ms_shell_cleanup(shell));
}

static int	ms_shell_main_loop(t_shell	*shell)
{
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
				if (ft_strlen(shell->cmd->line) > 0)
					add_history(shell->cmd->line);
				shell->status = ms_exec(shell);
				ms_cmd_cleanup(shell->cmd);
			}
			else
				ms_error_management(shell);
		}
	}
	return (shell->status);
}
