/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:15:57 by mgulenay          #+#    #+#             */
/*   Updated: 2022/07/11 16:49:38 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_if_int(char *str )
{
	int	i;

	i = 0;
	if (!str[i])
		return (1);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		return (0);
	if (!ft_isdigit(str[i]))
		return (1);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	return (0);
}

int	ms_exit(t_shell *shell)
{
	int	status;

	status = 0;
	if (shell->cmd->args[1] != NULL)
	{	
		status = ft_atoi(shell->cmd->args[1]);
		if (ms_args_len(shell->cmd->args) > 2 && check_if_int(shell->cmd->args[1]) == 0)
		{
			printf("minishell: exit: too many arguments\n");
			return (0);
		}
		if (check_if_int(shell->cmd->args[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", shell->cmd->args[1]);
			status = 2;
		}
		else if (status)
			status = ft_atoi(shell->cmd->args[1]) % 256;
	}
	printf("exit\n");
	ms_shell_cleanup(shell);
	exit(status);
}
