/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:50:02 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/13 18:48:48 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	ms_export_order_innerloop(t_envvar *temp, t_list *env);

t_node	*ms_env_find_entry(t_list *env, char *name)
{
	t_node		*node;
	t_node		*search;
	t_envvar	*line;
	int			i;

	node = NULL;
	search = env->first;
	i = 0;
	while (name[i] != '=' && name[i] != '\0')
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

int	ms_export_order(t_list *env)
{
	t_envvar	*temp;

	temp = ft_calloc(1, sizeof(t_envvar));
	if (temp == NULL)
		return (ALLOCATION_PROBLEM_EXIT);
	ms_export_order_innerloop(temp, env);
	free (temp);
	return (0);
}

static void	ms_export_order_innerloop(t_envvar *temp, t_list *env)
{
	t_node		*node;
	t_envvar	*line;
	t_envvar	*nline;
	int			swap;

	swap = 0;
	node = env->first;
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
}
