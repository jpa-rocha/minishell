/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:55:41 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/06 10:42:20 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ms_signal_handler(int num);
static void ms_signal_sigint(void);
static void	ms_signal_sigquit(void);

void	ms_signals(void)
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
		ms_signal_sigint();
	else if (num == SIGQUIT)
		ms_signal_sigquit();
}

static void	ms_signal_sigint()
{
	printf("\r");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

static void	ms_signal_sigquit()
{
	printf("\b\b");
	return ;
}
