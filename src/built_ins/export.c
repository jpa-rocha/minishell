/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:47:44 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/12 14:06:00 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ms_export_empty_call(t_node *node, t_envvar *line);

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
	return (0);
}
// SHOULD BE ALPHABETIC -> Empty declaration of minishell
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