/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:55:41 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/07 11:21:52 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ms_signal_handler(int num);
static void ms_signal_sigint();
static void	ms_signal_sigquit();

void	ms_signals(void)
{
  struct sigaction sa;

  sa.sa_handler = ms_signal_handler;
  sigaction(SIGINT, &sa, NULL);
}

static void ms_signal_handler(int num)
{
	if (num == SIGINT)
	  ms_signal_sigint();
	else if (num == EOF)
	  ms_signal_sigquit();
}

static void ms_signal_sigint()
{
  write(1, "^C", 2);
}

static void ms_signal_sigquit()
{
  printf("ctrl-d\n");
}
