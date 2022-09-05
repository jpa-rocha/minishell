/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 09:27:39 by jrocha            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/25 10:03:09 by jrocha           ###   ########.fr       */
=======
/*   Updated: 2022/08/25 21:24:52 by mgulenay         ###   ########.fr       */
>>>>>>> mgulenay
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_unset_var_exists(t_shell *shell, t_node *node);
static int	ms_unset_free_lines(t_shell *shell, t_node *node, t_envvar *line);

int	ms_unset(t_shell *shell, char **args)
{
	t_node		*node;

	if (ms_args_len(args) == 1)
	{
		shell->exitcode = EXIT_SUCCESS;
		return (shell->exitcode);
	}
	if (ms_var_check(shell, "unset", args[1]) == -1)
		return (shell->exitcode);
	node = ms_env_find_entry(shell->workenv, args[1]);
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