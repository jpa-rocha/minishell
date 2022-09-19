/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:15:57 by mgulenay          #+#    #+#             */
/*   Updated: 2022/09/19 12:28:34 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

/* test  */
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

static void	print_helper(void)
{
	printf("exit\n");
	printf("minishell: exit: too many arguments\n");
}

static void	exit_helper(t_shell *shell)
{
	printf("exit\n");
	ms_cmd_cleanup(shell->cmd);
}

static void	helper(t_shell *shell)
{
	printf("exit\n");
	ft_printf(STDERR_FILENO, EXIT_MSG, shell->cmd->curr_cmd[1]);
}

int	ms_exit(t_shell *shell)
{
	int	status;
	int	n_args;

	n_args = ms_args_len(shell->cmd->curr_cmd);
	status = 0;
	if (shell->cmd->curr_cmd[1] != NULL)
	{	
		status = ft_atoi(shell->cmd->curr_cmd[1]);
		if (n_args > 2 && check_if_int(shell->cmd->curr_cmd[1]) == 0)
		{
			print_helper();
			return (0);
		}
		else if (check_if_int(shell->cmd->curr_cmd[1]))
		{
			helper(shell);
			status = 2;
			ms_cmd_cleanup(shell->cmd);
			exit(status);
		}
		else if (status)
			status = ft_atoi(shell->cmd->curr_cmd[1]) % 256;
	}
	exit_helper(shell);
	exit(shell->status);
}
