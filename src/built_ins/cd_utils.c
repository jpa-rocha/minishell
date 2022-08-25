/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgulenay <mgulenay@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:56:23 by jrocha            #+#    #+#             */
/*   Updated: 2022/08/25 21:54:38 by mgulenay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	**ms_cd_alloc_setter(char *update);

int	ms_cd_new_path(t_shell *shell, t_envvar *path)
{	
	char		**setter;
	char		*update;

	update = NULL;
	update = getcwd(update, 1024);
	if (path == NULL)
	{
		setter = ms_cd_alloc_setter(update);
		if (setter == NULL)
			return (ALLOCATION_PROBLEM_EXIT);
		ft_strlcpy(setter[1], "PWD=", ft_strlen("PWD=") + 1);
		ft_strlcpy(&setter[1][ft_strlen(setter[1])], update, ft_strlen(update) + 1);
		ms_export(shell, setter);
		ms_free_args(setter);
	}
	if (update != NULL)
		free(update);
	return (EXIT_SUCCESS);
}

int	ms_cd_new_oldpath(t_shell *shell, t_envvar *oldpath)
{
	char		**setter;
	char		*update;

	update = NULL;
	update = getcwd(update, 1024);
	if (oldpath == NULL)
	{
		setter = ms_cd_alloc_setter(update);
		if (setter == NULL)
			return (ALLOCATION_PROBLEM_EXIT);
		ft_strlcpy(setter[1], "OLDPWD=", ft_strlen("OLDPWD="));
		ft_strlcpy(&setter[1][ft_strlen(setter[1])], update, ft_strlen(update) + 1);
		ms_export(shell, setter);
		ms_free_args(setter);
	}
	if (update != NULL)
		free(update);
	return (EXIT_SUCCESS);
}

int	ms_cd_switch_path(t_envvar *oldpath, char *newpath)
{
	free(oldpath->value);
	oldpath->value = ft_calloc(ft_strlen(newpath) + 2, sizeof(char));
	if (oldpath->value == NULL)
		return (ALLOCATION_PROBLEM_EXIT);
	ft_strlcpy(oldpath->value, newpath, ft_strlen(newpath) + 1);
	return (EXIT_SUCCESS);
}

t_envvar	*ms_init_vars(t_shell *shell, char *envvar)
{
	t_envvar	*var;

	var = NULL;
	if (ms_env_find_entry(shell->workenv, envvar) != NULL)
		var = (t_envvar *)ms_env_find_entry(shell->workenv, envvar)->data;
	shell->exitcode = EXIT_SUCCESS;
	return (var);
}

static char	**ms_cd_alloc_setter(char *update)
{
	char	**setter;

	setter = ft_calloc(2, sizeof(char *));
	if (setter == NULL)
		return (NULL);
	setter[1] = ft_calloc(4 + ft_strlen(update) + 1, sizeof(char));
	if (setter[1] == NULL)
		return (NULL);
	return (setter);
}
