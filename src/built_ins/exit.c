/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:15:57 by mgulenay          #+#    #+#             */
/*   Updated: 2022/07/14 23:36:52 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

int	ms_exit(t_shell *shell)
{
	int	status;
	int	n_args;

	n_args = ms_args_len(shell->cmd->args);
	status = 0;
	if (shell->cmd->args[1] != NULL)
	{	
		status = ft_atoi(shell->cmd->args[1]);
		if (n_args > 2 && check_if_int(shell->cmd->args[1]) == 0)
		{
			printf("exit\n");
			printf("minishell: exit: too many arguments\n");
			return (0);
		}
		else if (check_if_int(shell->cmd->args[1]))
		{
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", shell->cmd->args[1]);
			status = 2;
			exit(status);
		}
		else if (status)
		{
			status = ft_atoi(shell->cmd->args[1]) % 256;
		}
	}
	printf("exit\n");
	ms_shell_cleanup(shell);
	exit(status);
}
