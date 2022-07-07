/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:50:08 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/05 13:51:48 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_valid_command(char **args);

int ms_exec(char **args)
{
  if (ms_valid_command(args) != 0)
    return (1);
  return (0);
}

// Check if arguments are valid commands, if not print error
// message and return
static int	ms_valid_command(char **args)
{
	int i;

	i = 0;
	while (i <= ms_args_len(args) && ms_args_len(args) > 0)
	{
		if (access(args[i], F_OK) == -1)
		{
			printf("%s%s", args[i], ERR_INV);
			return (1);
		}
		if (access(args[i], F_OK) != -1) {
			printf("%s: lets do it\n", args[i]);
			return (0);
		}
		i += 1;
	}
	return (2);
}
