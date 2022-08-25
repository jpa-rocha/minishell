/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:37:40 by jrocha            #+#    #+#             */
/*   Updated: 2022/08/24 15:31:47 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

// Collects error numbers, and outputs the correct error message, in case the
// error occurs after allocations were made, a cleanup function must be called.
int	ms_error_management(t_shell *shell)
{
	if (shell == NULL)
	{
		printf("%s", ERR_NULL);
		return (ALLOCATION_PROBLEM_EXIT);
	}
	if (shell->exitcode == ALLOCATION_PROBLEM_EXIT)
	{
		ms_cmd_cleanup(shell->cmd);
		printf("%s", ERR_NULL);
	}
	return (shell->exitcode);
}

void	ms_list_data_cleaner(t_list *list)//, void *del)
{
	t_node		*last;
	t_envvar	*env_line;

	last = list->last;
	while (last->prev != NULL)
	{
		env_line = (t_envvar *) last->data;
		if (env_line->name != NULL)
			free(env_line->name);
		if (env_line->value != NULL)
			free(env_line->value);
		last = last->prev;
	}
	env_line = (t_envvar *)list->first->data;
	if (env_line->name != NULL)
		free(env_line->name);
	if (env_line->value != NULL)
		free(env_line->value);
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

int	ms_args_len(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
		i += 1;
	return (i);
}

