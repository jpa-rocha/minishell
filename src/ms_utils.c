/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:37:40 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/10 22:25:59 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// Collects error numbers, and outputs the correct error message, in case the
// error occurs after allocations were made, a cleanup function must be called.
int ms_error_management(int errnum)
{
  if (errnum == 1)
    printf("%s", ERR_ARG);
  if (errnum == 2)
    printf("%s", ERR_NULL);
  return (errnum);
}

void	ms_list_data_cleaner(t_list *list)
{
	t_node		*last;
	t_envvar	*line;

	last = list->last;
	while (last->prev != NULL)
	{
		line = (t_envvar *) last->data;
		if (line->name != NULL)
			free(line->name);
		if (line->value != NULL)
			free(line->value);
		last = last->prev;
	}
	line = (t_envvar *)list->first->data;
	if (line->name != NULL)
		free(line->name);
	if (line->value != NULL)
		free(line->value);
}

int	ms_list_env_len(t_list *env)
{
	int		i;
	t_node	*node;

	i = 0;
	node = env->first;
	while (node)
	{
		node = node->next;
		i++;
	}	
	return (i);
}