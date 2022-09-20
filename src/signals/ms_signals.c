/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:55:41 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/20 11:33:22 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

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

