/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:41:05 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/11 16:52:29 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// Entry point for the minishell logic
static int	ms_shell(char **env, char **argv);

int	main(int argc, char **argv, char **env)
{
	if (argc > 1 || !argv[0])
		return (ms_error_management(1));
	ms_shell(env, argv);
	return (0);
}

// Entry point for the minishell logic
static int	ms_shell(char **env, char **argv)
{
	t_shell	*shell;

	ms_logo();
	//ms_signals();
	shell = ms_shell_init(env, argv);
    while (1)
	{
		shell->cmd = ms_cmd_init(env, argv);
		if (shell->cmd->line == NULL)
		  break ;
		if (ms_parser(shell) != 0)
			return (ms_error_management(shell->errnum));
		//add_history(shell->cmd->line);
		ms_exec(shell);
		ms_cmd_cleanup(shell->cmd);
    }
	write(1, "exit\n", 5);
    return (ms_shell_cleanup(shell));
}
