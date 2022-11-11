/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 11:50:02 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/22 12:46:04 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*ms_export_name_cleanup(char *name);

t_node	*ms_env_find_entry(t_list *env, char *name)
{
	t_node		*node;
	t_node		*search;
	t_envvar	*line;
	char		*new_name;
	int			i;

	new_name = ms_export_name_cleanup(name);
	node = NULL;
	search = env->first;
	while (search)
	{
		line = (t_envvar *) search->data;
		i = ms_export_size_adjust(line);
		if (ft_strncmp(line->name, new_name, ft_strlen(line->name) - i) == 0
			&& ft_strlen(line->name) - i == ft_strlen(new_name))
		{
			node = search;
			break ;
		}
		search = search->next;
	}
	free(new_name);
	return (node);
}

static char	*ms_export_name_cleanup(char *name)
{
	char	*new;
	char	*new_name;
	int		i;

	new = ft_strchr(name, '=');
	if (new == NULL)
		new_name = ft_strdup(name);
	else
	{
		i = 0;
		while (name[i] != '=')
			i += 1;
		new_name = ft_calloc(i + 1, sizeof(char));
		ft_strlcpy(new_name, name, i + 1);
	}
	return (new_name);
}

int	ms_export_order(t_list *env)
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
			if (ms_env_swap_data(line, nline) == ALLOCATION_PROBLEM_EXIT)
				return (ALLOCATION_PROBLEM_EXIT);
			node = env->first;
			swap = 1;
		}
		if (swap == 0)
			node = node->next;
	}
	return (EXIT_SUCCESS);
}

int	ms_env_swap_data(t_envvar *line, t_envvar *nline)
{
	t_envvar	*temp;

	temp = ft_calloc(1, sizeof(t_envvar));
	if (temp == NULL)
		return (ALLOCATION_PROBLEM_EXIT);
	ft_memmove(temp, line, sizeof(t_envvar));
	ft_memmove(line, nline, sizeof(t_envvar));
	ft_memmove(nline, temp, sizeof(t_envvar));
	free(temp);
	return (EXIT_SUCCESS);
}

int	ms_var_check(t_shell *shell, char *called_from, char *newvar)
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
			|| ft_isdigit(newvar[0]) == 1 || newvar[i] == '-'
			|| newvar[i] == '$')
			first_check = 1;
		if (ft_isdigit(newvar[i]) != 1)
			check = 1;
		i += 1;
	}
	i += 2;
	if (first_check == 1 || check != 1)
	{
		shell->status = 1;
		printf(ERR_INV_ID, called_from, newvar);
		return (-1);
	}
	return (i);
}
