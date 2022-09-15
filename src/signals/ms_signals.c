/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:55:41 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/14 22:58:31 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ms_signal_handler(int num);
static void ms_signal_sigint(void);
static void	ms_signal_sigquit(void);

void	ms_signals()
{
	signal(SIGINT, ms_signal_handler);
	signal(SIGQUIT, ms_signal_handler);
}

static void	ms_signal_handler(int num)
{	
	if (num == SIGINT)
		ms_signal_sigint();
	if (num == SIGQUIT)
		ms_signal_sigquit();
}

static void	ms_signal_sigint(void)
{
	int	id;

	ft_printf(STDERR_FILENO, "get new_id\n");
	id = ms_pid_setter(-2);
	if (id == -1)
	{	
		ft_printf(STDOUT_FILENO, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ft_printf(STDERR_FILENO, "PARENT\n");
	}
	if (id > -1)
	{
		ft_printf(STDERR_FILENO, "CHILD\n");
		kill(id, SIGINT);
	}
	return ;
}

void	ms_signal_sigquit(void)
{
	int id;

	id = ms_pid_setter(-2);
	if (id == -1)
		ft_printf(STDOUT_FILENO, "\b\b  \b\b");
	if (id != -1)
	{
		ft_printf(STDERR_FILENO, "\b\b\\Quit (core dumped)\n");
		kill(id, SIGQUIT);
	}	
	
	return ;
}

int		ms_pid_setter(int id)
{
	static int	new_id;
	
	if (id == -1)
	{
		new_id = -1;
	//	ft_printf(STDERR_FILENO,"new_id: %i\n", new_id);
		return (new_id);
	}
	if (id > new_id)
		new_id = id;
	//ft_printf(STDERR_FILENO,"new_id: %i\n", new_id);
	return (new_id);
}