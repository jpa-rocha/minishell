/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:55:28 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/08 13:45:35 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ms_env(char **env)
{
	int	i;

	i = 0;
	while (i < ms_args_len(env))
	{
		printf("%s\n", env[i]);
		i += 1;
	}
}

char	**ms_create_env(char **env, char **argv)
{
	char	**newenv;
	int		i;

	i = 0;
	newenv = ft_calloc(ms_args_len(env), sizeof(char *));
	if (newenv == NULL)
		return (NULL);
	while (env[0][i] != '=')
		i += 1;
	i += 2;
	newenv[0] = ft_calloc(i + ft_strlen(argv[0]), sizeof(char));
	ft_strlcpy(newenv[0], env[0], i);
	ft_strlcpy(ft_strchr(newenv[0], '=') + 1, argv[0], ft_strlen(argv[0]) + 1);
	i = 1;
	while (i < ms_args_len(env))
	{
		newenv[i] = ft_strdup(env[i]);
		if (newenv[i] == NULL)
		{
			ms_free_args(newenv);
			return (NULL);
		}
		i += 1;
	}
	return (newenv);
}
