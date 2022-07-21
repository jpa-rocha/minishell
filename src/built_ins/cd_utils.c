/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:56:23 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/21 15:38:06 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ms_cd_new_path(t_shell *shell, t_envvar *path)
{	
	char		*setter;
	char		*update;

	update = NULL;
	update = getcwd(update, 1024);
	if (path == NULL)
	{
		setter = ft_calloc(4 + ft_strlen(update) + 1, sizeof(char));
		if (setter == NULL)
			return (ALLOCATION_PROBLEM_EXIT);
		ft_strlcpy(setter, "PWD=", ft_strlen("PWD=") + 1);
		ft_strlcpy(&setter[ft_strlen(setter)], update, ft_strlen(update) + 1);
		ms_export(shell, setter);
		free(setter);
	}
	if (update != NULL)
		free(update);
	return (EXIT_SUCCESS);
}

int	ms_cd_new_oldpath(t_shell *shell, t_envvar *oldpath)
{
	char		*setter;
	char		*update;

	update = NULL;
	update = getcwd(update, 1024);
	if (oldpath == NULL)
	{
		setter = ft_calloc(7 + ft_strlen(update) + 1, sizeof(char));
		if (setter == NULL)
			return (ALLOCATION_PROBLEM_EXIT);
		ft_strlcpy(setter, "OLDPWD=", ft_strlen("OLDPWD="));
		ft_strlcpy(&setter[ft_strlen(setter)], update, ft_strlen(update) + 1);
		ms_export(shell, setter);
		free(setter);
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
