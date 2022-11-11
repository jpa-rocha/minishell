/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:37:40 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/22 10:43:54 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

/// Collects error numbers, and outputs the correct error message, in case the
// error occurs after allocations were made, a cleanup function must be called.
int	ms_error_management(t_shell *shell)
{
	if (shell == NULL)
	{
		printf("%s", ERR_NULL);
		return (ALLOCATION_PROBLEM_EXIT);
	}
	if (shell->status == ALLOCATION_PROBLEM_EXIT)
	{
		ms_cmd_cleanup(shell->cmd);
		printf("%s", ERR_NULL);
	}
	if (shell->status == EXIT_FAILURE)
	{
		ms_cmd_cleanup(shell->cmd);
	}
	return (shell->status);
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

char	**ms_copy_cmd(char **cmd)
{
	char	**copy;
	int		i;
	int		len;

	if (cmd == NULL)
		return (NULL);
	i = 0;
	len = ms_args_len(cmd);
	copy = ft_calloc(len + 1, sizeof(char *));
	if (copy == NULL)
		return (NULL);
	while (i < len)
	{
		copy[i] = ft_strdup(cmd[i]);
		i += 1;
	}
	copy[i] = NULL;
	return (copy);
}

char	*ms_env_ret_value(t_shell *shell, char *name)
{
	t_node		*node;
	t_envvar	*var;
	char		*search;

	if (ft_strlen(name) > 0)
	{
		search = ft_strdup(name);
		node = ms_env_find_entry(shell->workenv, name);
		if (node == NULL)
		{
			free(search);
			return (NULL);
		}
		var = (t_envvar *)node->data;
		free(search);
		search = ft_strdup(var->value);
		return (search);
	}
	search = ft_calloc(1, sizeof(char));
	return (search);
}
