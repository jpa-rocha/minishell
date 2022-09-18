/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:55:28 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/16 11:30:04 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static t_envvar	ms_env_create_data(t_shell *shell, char *env_line, int order);

int	ms_env(t_shell *shell)
{
	t_envvar	*line;
	t_node		*node;
	int			i;

	i = 0;
	node = shell->workenv->first;
	while (i < shell->workenv->total)
	{
		line = (t_envvar *) node->data;
		if (line->env_order == i)
		{
			if (line->name[ft_strlen(line->name) - 1] == '=')
			{
				printf("%s", line->name);
				printf("%s\n", line->value);
			}
			node = shell->workenv->first;
			i ++;
		}
		else
			node = node->next;
	}
	shell->status = EXIT_SUCCESS;
	return (shell->status);
}

t_list	*ms_env_create_work_env(t_shell *shell, char **env)
{
	t_list		*w_env;
	t_envvar	data;
	int			i;

	i = 0;
	w_env = list_creator(ms_args_len(env), sizeof(t_envvar));
	while (i < ms_args_len(env))
	{
		data = ms_env_create_data(shell, env[i], i);
		list_add_back(&data, w_env);
		i += 1;
	}
	return (w_env);
}

static t_envvar	ms_env_create_data(t_shell *shell, char *env_line, int order)
{
	t_envvar	line;
	char		*value;
	int			i;

	i = 0;
	while (env_line[i] != '=' && env_line[i] != '\0')
		i += 1;
	i += 2;
	line.name = ft_calloc(i, sizeof(char));
	line.env_order = order;
	ft_strlcpy(line.name, env_line, i);
	if (ft_strncmp(line.name, "SHELL=", 5) == 0)
		line.value = ft_strdup(shell->name);
	else if (ft_strncmp(line.name, "SHLVL=", 5) == 0)
		line.value = ft_itoa(shell->shlvl);
	else
	{	
		value = ft_strchr(env_line, '=');
		if (value != NULL)
			value += 1;
		i = ft_strlen(value);
		line.value = ft_calloc(i + 1, sizeof(char));
		ft_strlcpy(line.value, value, i + 1);
	}
	return (line);
}

char	**ms_env_init_env(t_shell *shell)
{
	char		**newenv;
	t_node		*node;
	t_envvar	*line;
	int			i;

	if (shell->env != NULL)
		ms_free_args(shell->env);
	i = 0;
	node = shell->workenv->first;
	newenv = ft_calloc(ms_list_env_len(shell->workenv) + 1, sizeof(char *));
	if (newenv == NULL)
		return (NULL);
	while (node)
	{
		line = (t_envvar *) node->data;
		newenv[i] = ft_strjoin(line->name, line->value);
		node = node->next;
		i += 1;
	}
	newenv[i] = NULL;
	return (newenv);
}
