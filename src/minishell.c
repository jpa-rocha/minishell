/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:41:05 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/10 18:36:19 by jrocha           ###   ########.fr       */
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


static int	ms_shell(char **env, char **argv)
{
	t_cmd	*cmd;
	
	ms_logo();
	//ms_signals();
        while (1)
	{
		cmd = ms_cmd_init(env, argv);
		if (cmd->line == NULL)
		{
			write(1, "exit\n", 5);
			break;
		}
		if (ms_parser(cmd) != 0)
			return (ms_error_management(cmd->errnum));
		//add_history(cmd->line);
		ms_exec(cmd->args);
		ms_cmd_cleanup(cmd);
        }
        return (ms_cmd_cleanup(cmd));
}
