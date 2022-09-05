/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 11:13:58 by mgulenay          #+#    #+#             */
/*   Updated: 2022/08/23 11:39:31 by jrocha           ###   ########.fr       */
=======
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 11:13:58 by mgulenay          #+#    #+#             */
/*   Updated: 2022/08/25 22:02:44 by mgulenay         ###   ########.fr       */
>>>>>>> mgulenay
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	n_check(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
		i++;
	else
	 	return (0);
	while (s[i] == 'n')
		i++;
	if (s[i] != '\0')
		return (0);
	return (1);
}

int	ms_echo(t_cmd *cmd)
{
	int		i;
	int		flag_n;

	flag_n = 0;	

	i = 1;
	while (cmd->curr_cmd[i] && n_check(cmd->curr_cmd[i]))
	{
		flag_n = 1;
		i++;
	}
	while (cmd->curr_cmd[i])
	{
		ft_putstr_fd(cmd->curr_cmd[i], 1);
		i++;
		if (cmd->curr_cmd[i])
			write (1, " ", 1);
	}
	if (flag_n == 1)
		write(1, "\n", 1);
	return (0);
}
