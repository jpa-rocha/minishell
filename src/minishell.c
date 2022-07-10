/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:41:05 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/10 14:19:34 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static int	ms_shell(char **env);

int	main(int argc, char **argv, char **env)
{
	if (argc > 1 || !argv[0])
	return (ms_error_management(1));
	ms_shell(env);
	return (0);
}

// Entry point for the minishell logic
static int	ms_shell(char **env)
{
	t_cmd	*cmd;

	ms_logo();
	ms_signals();
    while (1)
	{
		cmd = ms_cmd_init(env);
		if (cmd->line == NULL)
		  break ;
		if (ft_strncmp(cmd->line, "exit", 4) == 0)
		{
			printf("testing\n");
			//ms_pwd();
			ms_exit();
		}
		if (ms_parser(cmd) != 0)
		  return (ms_error_management(cmd->errnum));
		add_history(cmd->line);
		ms_exec(cmd->args);
		ms_cmd_cleanup(cmd);
    }
    return (ms_cmd_cleanup(cmd));
}
