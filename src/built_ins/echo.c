/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 11:13:58 by mgulenay          #+#    #+#             */
/*   Updated: 2022/07/10 14:25:53 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int		ms_echo(char **args)
{
	int	i;
	int	flag_n;

	flag_n = 0;
	if (!(cmd->args[1]))
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 1;
	if (ft_strncmp(cmd->args[1], "-n", 2) != 0)
	{
		flag_n = 1;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			write (1, " ", 1);
		i++;
	}
	if (flag_n == 0)
		write(1, "\n", 1);
	return (0);
}
