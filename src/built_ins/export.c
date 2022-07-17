/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:47:44 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/13 10:47:57 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ms_export_empty_call(t_node *node, t_envvar *line);
static int	ms_export_order(t_list *env);

int	ms_export(t_shell *shell, t_list *env, char *newvar)
{
	t_node		*node;
	t_envvar	*line;
	char		*value;

	node = env->first;
	line = (t_envvar *) node->data;
	shell->exitcode = ms_export_order(env);
	if (shell->exitcode == ALLOCATION_PROBLEM_EXIT)
		return (shell->exitcode);
	if (newvar == NULL)
		ms_export_empty_call(node, line);
	else
	{
		node = ms_env_find_entry(env, newvar);
		line = (t_envvar *) node->data;
		free(line->value);
		value = ft_strchr(newvar, '=');
		if (value)
			value += 1;
		line->value = ft_strdup(value);
		free(shell->env);
		shell->env = ms_env_init_env(env);
		shell->path = ms_shell_path_creator(shell);
	}
	shell->exitcode = 0;
	return (shell->exitcode);
}

static void	ms_export_empty_call(t_node *node, t_envvar *line)
{
	while (node)
	{
		line = (t_envvar *) node->data;
		printf("declare -x ");
		printf("%s", line->name);
		printf("\"%s\"\n", line->value);
		node = node->next;
	}
}

t_node	*ms_env_find_entry(t_list *env, char *name)
{
	t_node		*node;
	t_node		*search;
	t_envvar	*line;
	int			i;

	node = NULL;
	search = env->first;
	i = 0;
	while (name[i] != '=')
		i += 1;
	i += 1;
	while (search)
	{
		line = (t_envvar *) search->data;
		if (ft_strncmp(line->name, name, i) == 0)
		{
			node = search;
			break ;
		}
		search = search->next;
	}
	return (node);
}

// USE STRNCMP TO CHANGE LIST ORDER
static int	ms_export_order(t_list *env)
{
	t_node		*node;
	t_envvar	*line;
	t_envvar	*nline;
	t_envvar	*temp;
	int			swap;

	swap = 0;
	node = env->first;
	temp = ft_calloc(1, sizeof(t_envvar));
	if (temp == NULL)
		return (ALLOCATION_PROBLEM_EXIT);
	while (node != env->last)
	{
		swap = 0;
		line = (t_envvar *) node->data;
		nline = (t_envvar *) node->next->data;
		if (ft_strncmp(line->name, nline->name,
				ft_short_strlen(line->name, nline->name)) > 0)
		{
			ft_memmove(temp, line, sizeof(t_envvar));
			ft_memmove(line, nline, sizeof(t_envvar));
			ft_memmove(nline, temp, sizeof(t_envvar));
			node = env->first;
			swap = 1;
		}
		if (swap == 0)
			node = node->next;
	}
	free (temp);
	return (0);
}