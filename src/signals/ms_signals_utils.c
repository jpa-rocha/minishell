/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:31:56 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/20 11:32:44 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ms_here_signal_handler(int num)
{	
	if (num == SIGINT)
	{
		ft_printf(STDOUT_FILENO, "\b\b^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	if (num == SIGQUIT)
	{
		ft_printf(STDOUT_FILENO, "\b\b  \b\b");
	}
}

void	ms_parent_signal_handler(int num)
{	
	if (num == SIGINT)
	{
		ft_printf(STDOUT_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ms_child_signal_handler(int num)
{
	if (num == SIGINT)
	{
		ft_printf(STDERR_FILENO, "\n");
	}
	if (num == SIGQUIT)
	{
		ft_printf(STDERR_FILENO, "Quit (core dumped)\n");
	}
}