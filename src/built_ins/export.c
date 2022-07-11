/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:47:44 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/11 17:07:05 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ms_export_empty_call(t_node *node, t_envvar *line);
static t_node *ms_export_find_entry(t_list *env, char *newvar);
// SHOULD BE ALPHABETIC
int	ms_export(t_shell *shell, t_list *env, char *newvar)
{
	t_node		*node;
	t_envvar	*line;
	char		*value;

	node = env->first;
	line = (t_envvar *) node->data;
	if (newvar == NULL)
		ms_export_empty_call(node, line);
	else
	{
		node = ms_export_find_entry(env, newvar);
		line = (t_envvar *) node->data;
		free(line->value);
		value = ft_strchr(newvar, '=');
		if (value)
			value += 1;
		line->value = ft_strdup(value);
		free(shell->env);
		shell->env = ms_env_init_env(env);
	}
	return (0);
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

static t_node	*ms_export_find_entry(t_list *env, char *newvar)
{
	t_node		*node;
	t_node		*search;
	t_envvar	*line;
	int			i;

	node = NULL;
	search = env->first;
	i = 0;
	while (newvar[i] != '=')
		i += 1;
	i += 1;
	while (search)
	{
		line = (t_envvar *) search->data;
		if (ft_strncmp(line->name, newvar, i) == 0)
		{
			node = search;
			break ;
		}
		search = search->next;
	}
	return (node);
}