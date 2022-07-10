/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:15:57 by mgulenay          #+#    #+#             */
/*   Updated: 2022/07/10 14:28:57 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	check_if_int(char *s )
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
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	return (0);
}

int	ms_exit(void)
{
	int	status;

	status = cmd->args[1];
	
	if (cmd->num_args > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (0);
	}
	if (cmd->args[1] && !check_if_int(cmd->args[1]))
	{
		printf("minishell: exit: %s: numeric argument required", cmd->args[1]);
		return (0);
	}
	else if(status)
		status = ft_atoi(cmd->args[1] % 256);
	printf("exit\n");
	exit(status);
}
