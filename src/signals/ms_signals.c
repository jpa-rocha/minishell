/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:55:41 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/02 13:57:11 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ms_signal_handler(int num);
static void ms_signal_sigint();
static void	ms_signal_sigquit();

void	ms_signals_parent(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaddset(&sa.sa_mask, SIGTERM);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = ms_signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	ms_signal_child(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	/* sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT); */
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = ms_signal_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
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
	printf("\n");
	return ;
}

static void	ms_signal_sigquit()
{
	printf("\b\b");
	return ;
}
