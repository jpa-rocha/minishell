/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:15:57 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/22 13:21:53 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_exit_logic(t_shell *shell, char **args, int status);

static int	check_if_int(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (1);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static void	exit_helper(t_shell *shell)
{
	printf("exit\n");
	ms_cmd_cleanup(shell->cmd);
}

int	ms_exit(t_shell *shell, char **args)
{
	int	status;
	int	n_args;

	n_args = ms_args_len(args);
	status = 0;
	if (n_args == 1)
	{
		shell->status = status;
		exit_helper(shell);
		exit(shell->status);
	}
	if (n_args < 3)
	{
		if (check_if_int(args[1]) == 1)
		{
			shell->status = 2;
			ft_printf(STDERR_FILENO, EXIT_MSG, args[1]);
			return (shell->status);
		}
		ms_exit_logic(shell, args, status);
		exit(shell->status);
	}
	ft_printf(STDERR_FILENO, ERR_EXIT);
	shell->status = EXIT_FAILURE;
	return (shell->status);
}

static int	ms_exit_logic(t_shell *shell, char **args, int status)
{
	status = ft_atoi(args[1]);
	if (status > 255)
		status = status % 256;
	shell->status = status;
	exit_helper(shell);
	return (EXIT_SUCCESS);
}
