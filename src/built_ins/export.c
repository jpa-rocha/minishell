/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:47:44 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/14 17:06:22 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ms_export_empty_call(t_node *node);
static int	ms_export_var_exists(t_shell *shell, char *newvar, t_node *node);
static int	ms_create_var_check(t_shell *shell, char *newvar);
static int	ms_export_create_var(t_shell *shell, char *newvar);

int	ms_export(t_shell *shell, char *newvar)
{
	t_node		*node;

	node = shell->workenv->first;
	shell->exitcode = ms_export_order(shell->workenv);
	if (shell->exitcode == ALLOCATION_PROBLEM_EXIT)
		return (shell->exitcode);
	if (newvar == NULL)
		ms_export_empty_call(node);
	else
	{
		node = ms_env_find_entry(shell->workenv, newvar);
		if (node != NULL)
			ms_export_var_exists(shell, newvar, node);
		else
			shell->exitcode = ms_export_create_var(shell, newvar);
		if (shell->exitcode != 0)
			return (shell->exitcode);
	}
	shell->exitcode = 0;
	return (shell->exitcode);
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
	char		*value;

	line = (t_envvar *) node->data;
	free(line->value);
	value = ft_strchr(newvar, '=');
	if (value)
		value += 1;
	line->value = ft_strdup(value);
	free(shell->env);
	shell->env = ms_env_init_env(shell->workenv);
	shell->path = ms_shell_path_creator(shell);
	return (0);
}

// CONTROLL FOR NULL
static int	ms_export_create_var(t_shell *shell, char *newvar)
{
	t_envvar	line;
	char		*value;
	int			i;

	i = ms_create_var_check(shell, newvar);
	if (i < 0)
		return (shell->exitcode);
	line.name = ft_calloc(i, sizeof(char));
	line.env_order = shell->workenv->total;
	ft_strlcpy(line.name, newvar, i);
	value = ft_strchr(newvar, '=');
	if (value != NULL)
	{
		value += 1;
		i = ft_strlen(value);
		line.value = ft_calloc(i + 1, sizeof(char));
		ft_strlcpy(line.value, value, i + 1);
	}
	else
		line.value = ft_calloc(1, sizeof(char));
	list_add_back(&line, shell->workenv);
	shell->exitcode = 0;
	return (shell->exitcode);
}

static int	ms_create_var_check(t_shell	*shell, char *newvar)
{
	int	i;
	int	first_check;
	int	check;

	first_check = 0;
	check = 0;
	i = 0;
	while (newvar[i] != '=' && newvar[i] != '\0')
	{
		if (newvar[i] == '=' || newvar[i] == '%' || newvar[i] == '?'
			|| ft_isdigit(newvar[0]) == 1)
			first_check = 1;
		if (ft_isdigit(newvar[i]) != 1)
			check = 1;
		i += 1;
	}
	i += 2;
	if (first_check == 1 || check != 1)
	{
		shell->exitcode = 1;
		printf("minishell: export: `%s\': not a valid identifier\n", newvar);
		return (-1);
	}
	return (i);
}
