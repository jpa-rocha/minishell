/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:47:44 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/06 17:39:46 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ms_export_empty_call(t_node *node);
static int	ms_export_var_exists(t_shell *shell, char *newvar, t_node *node);
static int	ms_export_create_var(t_shell *shell, char *newvar);
static int	ms_export_value_check(t_shell *shell, t_envvar *line, char *newvar);

int	ms_export(t_shell *shell, char **args)
{
	t_node		*node;

	node = shell->workenv->first;
	shell->status = ms_export_order(shell->workenv);
	if (shell->status == ALLOCATION_PROBLEM_EXIT)
		return (shell->status);
	if (ms_args_len(args) == 1)
		ms_export_empty_call(node);
	else if (ms_args_len(args) > 1)
	{
		node = ms_env_find_entry(shell->workenv, args[1]);
		if (node != NULL)
			ms_export_var_exists(shell, args[1], node);
		else
			shell->status = ms_export_create_var(shell, args[1]);
		if (shell->status != EXIT_SUCCESS)
			return (shell->status);
	}
	shell->status = EXIT_SUCCESS;
	return (shell->status);
}

static void	ms_export_empty_call(t_node *node)
{
	t_envvar	*line;

	while (node)
	{
		line = (t_envvar *) node->data;
		printf("declare -x ");
		printf("%s", line->name);
		if (line->name[ft_strlen(line->name) - 1] == '=')
			printf("\"%s\"", line->value);
		printf("\n");
		node = node->next;
	}
}

// POSSIBLE PROBLEMS WITH NULL
static int	ms_export_var_exists(t_shell *shell, char *newvar, t_node *node)
{
	t_envvar	*line;
	int			i;

	line = (t_envvar *) node->data;
	free(line->name);
	free(line->value);
	i = ms_var_check(shell, "export", newvar);
	if (i < 0)
		return (shell->status);
	line->name = ft_calloc(i, sizeof(char));
	if (line->name == NULL)
	{
		shell->status = ALLOCATION_PROBLEM_EXIT;
		return (shell->status);
	}
	ft_strlcpy(line->name, newvar, i);
	shell->status = ms_export_value_check(shell, line, newvar);
	shell->env = ms_env_init_env(shell);
	shell->cmd->path = ms_cmd_path_creator(shell);
	return (shell->status);
}

// CONTROLL FOR NULL
static int	ms_export_create_var(t_shell *shell, char *newvar)
{
	t_envvar	line;
	int			i;

	i = ms_var_check(shell, "export", newvar);
	if (i < 0)
		return (shell->status);
	line.name = ft_calloc(i, sizeof(char));
	if (line.name == NULL)
	{
		shell->status = ALLOCATION_PROBLEM_EXIT;
		return (shell->status);
	}
	line.env_order = shell->workenv->total;
	ft_strlcpy(line.name, newvar, i);
	shell->status = ms_export_value_check(shell, &line, newvar);
	list_add_back(&line, shell->workenv);
	shell->status = EXIT_SUCCESS;
	return (shell->status);
}

static int	ms_export_value_check(t_shell *shell, t_envvar *line, char *newvar)
{
	char		*value;

	value = ft_strchr(newvar, '=');
	if (value != NULL)
	{
		value += 1;
		line->value = ft_calloc(ft_strlen(value) + 1, sizeof(char));
		if (line->value == NULL)
		{
			shell->status = ALLOCATION_PROBLEM_EXIT;
			return (shell->status);
		}
		ft_strlcpy(line->value, value, ft_strlen(value) + 1);
	}
	else
	{
		line->value = ft_calloc(1, sizeof(char));
		if (line->value == NULL)
		{
			shell->status = ALLOCATION_PROBLEM_EXIT;
			return (shell->status);
		}
	}
	shell->status = EXIT_SUCCESS;
	return (shell->status);
}