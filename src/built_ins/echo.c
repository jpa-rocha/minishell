/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 11:13:58 by mgulenay          #+#    #+#             */
/*   Updated: 2022/07/11 14:01:45 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ms_echo(t_cmd *cmd)
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
	if (ft_strncmp(cmd->args[1], "-n", 2) == 0)
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
