/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:55:41 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/19 10:52:36 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ms_parent_signal_handler(int num);
static void	ms_child_signal_handler(int num);
static void	ms_here_signal_handler(int num);

void	ms_signals_parent(void)
{
	signal(SIGINT, ms_parent_signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ms_signals_child(void)
{
	signal(SIGINT, ms_child_signal_handler);
	signal(SIGQUIT, ms_child_signal_handler);
}

void	ms_signals_heredoc(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, ms_here_signal_handler);
}

void	ms_signals_block(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	ms_here_signal_handler(int num)
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

static void	ms_parent_signal_handler(int num)
{	
	if (num == SIGINT)
	{
		ft_printf(STDOUT_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	ms_child_signal_handler(int num)
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