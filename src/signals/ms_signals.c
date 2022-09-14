/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:55:41 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/14 10:32:11 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ms_signal_handler(int num);
static void ms_signal_sigint(pid_t id);
static void	ms_signal_sigquit(pid_t id);

void	ms_signals()
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = ms_signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

static void	ms_signal_handler(int num)
{	
	if (num == SIGINT)
		ms_signal_sigint(0);
	else if (num == SIGQUIT)
		ms_signal_sigquit(1);
}

static void	ms_signal_sigint(pid_t id)
{
	if (id != 0)
	{	
		ft_printf(STDOUT_FILENO, "\r");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		kill(id, SIGINT);
	return ;
}

static void	ms_signal_sigquit(pid_t id)
{
	if (id == 0)
		ft_printf(STDOUT_FILENO, "\b\b^\\Quit (core dumped)\n");

	return ;
}
