/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 09:27:39 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/22 10:03:11 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_unset_var_exists(t_shell *shell, t_node *node);
static int	ms_unset_free_lines(t_shell *shell, t_node *node, t_envvar *line);
static int	ms_unset_inner_loop(t_shell *shell, char **args, int i);

int	ms_unset(t_shell *shell, char **args)
{
	int			i;

	i = 1;
	if (ms_args_len(args) == 1)
	{
		shell->status = EXIT_SUCCESS;
		return (shell->status);
	}
	while (i < ms_args_len(args))
	{
		shell->status = ms_unset_inner_loop(shell, args, i);
		i += 1;
	}
	shell->status = EXIT_SUCCESS;
	return (shell->status);
}

static int	ms_unset_inner_loop(t_shell *shell, char **args, int i)
{
	t_node		*node;

	if (ms_var_check(shell, "unset", args[i]) == -1)
		return (shell->status);
	node = ms_env_find_entry(shell->workenv, args[i]);
	if (node != NULL)
	{
		ms_unset_var_exists(shell, node);
		shell->status = ms_export_order(shell->workenv);
		shell->env = ms_env_init_env(shell);
		if (shell->cmd->path != NULL)
			ms_free_args(shell->cmd->path);
		shell->cmd->path = ms_cmd_path_creator(shell);
	}
	return (EXIT_SUCCESS);
}

static int	ms_unset_var_exists(t_shell *shell, t_node *node)
{
	t_envvar	*line;
	int			env_order;

	line = (t_envvar *)node->data;
	env_order = line->env_order;
	shell->status = ms_unset_free_lines(shell, node, line);
	if (shell->status != EXIT_SUCCESS)
		return (shell->status);
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
		shell->status = ALLOCATION_PROBLEM_EXIT;
	return (shell->status);
}

static int	ms_unset_free_lines(t_shell *shell, t_node *node, t_envvar *line)
{
	t_envvar	*last;

	if (node != shell->workenv->last)
	{
		last = (t_envvar *) shell->workenv->last->data;
		shell->status = ms_env_swap_data(line, last);
		if (shell->status != EXIT_SUCCESS)
			return (shell->status);
		free(last->name);
		free(last->value);
	}
	else
	{
		free(line->name);
		free(line->value);
	}
	ft_memset(shell->workenv->last->data, 0, shell->workenv->data_size);
	return (shell->status);
}

int	ms_unset_var(t_shell *shell, char *var)
{
	char	**unset;

	unset = ft_calloc(3, sizeof(char *));
	unset[0] = ft_strdup("unset");
	unset[1] = ft_strdup(var);
	unset[2] = NULL;
	ms_unset(shell, unset);
	ms_free_args(unset);
	return (EXIT_SUCCESS);
}
