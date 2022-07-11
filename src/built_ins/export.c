/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 13:47:44 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/11 10:43:27 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ms_export(t_list *env, char *newvar)
{
	t_node		*node;
	t_envvar	*line;

	node = env->first;
	if (newvar == NULL)
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
	return (0);
}