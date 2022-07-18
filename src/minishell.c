/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:41:05 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/18 17:22:15 by mgulenay         ###   ########.fr       */
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

	ms_logo();
	ms_signals();
	shell = ms_shell_init(env, argv);
	if (shell == NULL)
		return (ms_error_management(shell));
	while (1)
	{
		shell->cmd = ms_cmd_init(shell);
		int n = get_nmb_cmd(shell->cmd);
		printf("%d\n", n);
		//ms_lexer(shell->cmd);
/* 		int i=0;
		while (i < shell->cmd->n_cmd)
		{
			printf("%s\n", shell->cmd);
			i++;
		} */
/* 		if                                                                                                                                                                                                                                  (shell->cmd == NULL)
			ms_error_management(shell);
		if (shell->exitcode == 0)
		{
			if (shell->cmd->line == NULL)
				break ; 
 			if (ms_parser(shell) != 0)
				return (ms_error_management(shell));
			add_history(shell->cmd->line);
			ms_exec(shell);
			ms_cmd_cleanup(shell->cmd);
		} */
		ms_parser(shell);
		add_history(shell->cmd->line);
	}
	write(1, "exit\n", 5);
	return (ms_shell_cleanup(shell));
}
