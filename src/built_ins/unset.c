/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 09:27:39 by jrocha            #+#    #+#             */
/*   Updated: 2022/08/18 12:41:50 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_unset_var_exists(t_shell *shell, t_node *node);
static int	ms_unset_free_lines(t_shell *shell, t_node *node, t_envvar *line);

int	ms_unset(t_shell *shell, char *to_unset)
{
	t_node		*node;

	if (to_unset == NULL)
	{
		shell->exitcode = EXIT_SUCCESS;
		return (shell->exitcode);
	}
	if (ms_var_check(shell, "unset", to_unset) == -1)
		return (shell->exitcode);
	node = ms_env_find_entry(shell->workenv, to_unset);
	if (node != NULL)
	{
		ms_unset_var_exists(shell, node);
		if (shell->exitcode != EXIT_SUCCESS)
			return (shell->exitcode);
		shell->exitcode = ms_export_order(shell->workenv);
		shell->env = ms_env_init_env(shell);
		shell->cmd->path = ms_cmd_path_creator(shell);
	}
	shell->exitcode = EXIT_SUCCESS;
	return (shell->exitcode);
}

static int	ms_unset_var_exists(t_shell *shell, t_node *node)
{
	t_envvar	*line;
	int			env_order;

	line = (t_envvar *)node->data;
	env_order = line->env_order;
	shell->exitcode = ms_unset_free_lines(shell, node, line);
	if (shell->exitcode != EXIT_SUCCESS)
		return (shell->exitcode);
	shell->workenv->last = shell->workenv->last->prev;
	shell->workenv->last->next = NULL;
	shell->workenv->current = shell->workenv->last;
	node = shell->workenv->first;
	while (node)
	{
		line = (t_envvar *) node->data;
		if (line->env_order > env_order)
			line->env_order -= 1;
		node = node->next;
	}
	shell->workenv->total -= 1;
	if (shell->workenv->total < (int) shell->workenv->capacity / 4)
		list_resize(shell->workenv, (int) shell->workenv->capacity / 4);
	if (shell->workenv->nodes == NULL)
		shell->exitcode = ALLOCATION_PROBLEM_EXIT;
	return (shell->exitcode);
}

static int	ms_unset_free_lines(t_shell *shell, t_node *node, t_envvar *line)
{
	t_envvar	*last;

	if (node != shell->workenv->last)
	{
		last = (t_envvar *) shell->workenv->last->data;
		shell->exitcode = ms_env_swap_data(line, last);
		if (shell->exitcode != EXIT_SUCCESS)
			return (shell->exitcode);
		free(last->name);
		free(last->value);
	}
	else
	{
		free(line->name);
		free(line->value);
	}
	ft_memset(shell->workenv->last->data, 0, shell->workenv->data_size);
	return (shell->exitcode);
}
