/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 10:41:05 by jrocha            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/07/10 18:36:19 by jrocha           ###   ########.fr       */
=======
/*   Updated: 2022/07/10 14:19:34 by mgulenay         ###   ########.fr       */
>>>>>>> mgulenay
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

<<<<<<< HEAD

static int	ms_shell(char **env, char **argv)
=======
// Entry point for the minishell logic
static int	ms_shell(char **env)
>>>>>>> mgulenay
{
	t_cmd	*cmd;

	ms_logo();
<<<<<<< HEAD
	//ms_signals();
        while (1)
=======
	ms_signals();
    while (1)
>>>>>>> mgulenay
	{
		cmd = ms_cmd_init(env, argv);
		if (cmd->line == NULL)
<<<<<<< HEAD
		{
			write(1, "exit\n", 5);
			break;
=======
		  break ;
		if (ft_strncmp(cmd->line, "exit", 4) == 0)
		{
			printf("testing\n");
			//ms_pwd();
			ms_exit();
>>>>>>> mgulenay
		}
		if (ms_parser(cmd) != 0)
			return (ms_error_management(cmd->errnum));
		//add_history(cmd->line);
		ms_exec(cmd->args);
		ms_cmd_cleanup(cmd);
    }
    return (ms_cmd_cleanup(cmd));
}
