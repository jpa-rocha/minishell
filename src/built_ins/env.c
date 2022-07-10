/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:55:28 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/10 22:22:21 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static t_envvar	ms_env_create_data(char *env_line, char **argv);

void	ms_env(t_list *env)
{
	t_envvar	*line;
	t_node		*node;

	node = env->first;
	while (node->next != NULL)
	{
		line = (t_envvar *) node->data;
		printf("%s", line->name);
		printf("%s\n", line->value);
		node = node->next;
	}
}

t_list	*ms_env_create_work_env(char **env, char **argv)
{
	t_list		*w_env;
	t_envvar	data;
	int			i;

	i = 0;
	w_env = list_creator(ms_args_len(env), sizeof(t_envvar));
	while (i < ms_args_len(env))
	{
		data = ms_env_create_data(env[i], argv);
		list_add_back(&data, w_env);
		i += 1;
	}
	return (w_env);
}

static t_envvar	ms_env_create_data(char *env_line, char **argv)
{
	t_envvar	line;
	char		*value;
	int			i;

	(void) argv;
	i = 0;
	while (env_line[i] != '=')
		i += 1;
	i += 2;
	line.name = ft_calloc(i, sizeof(char));
	ft_strlcpy(line.name, env_line, i);
	if (ft_strncmp(line.name, "SHELL=", 5) == 0)
		line.value = ft_strdup(argv[0]);
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

char	**ms_env_init_env(t_list *env)
{
	char		**newenv;
	t_node		*node;
	t_envvar	*line;
	int			i;

	i = 0;
	node = env->first;
	newenv = ft_calloc(ms_list_env_len(env) + 1, sizeof(char *));
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

