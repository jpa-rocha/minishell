/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:56:23 by jrocha            #+#    #+#             */
/*   Updated: 2022/09/15 20:48:15 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	**ms_cd_alloc_setter(char *update);

int	ms_cd_new_path(t_shell *shell, t_envvar *path, char *var)
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
		ft_strlcpy(setter[1], var, ft_strlen(var) + 1);
		ft_strlcpy(&setter[1][ft_strlen(setter[1])],
			update, ft_strlen(update) + 1);
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

int	ms_cd_path_exists(t_shell *shell, t_envvar *path,
				t_envvar *oldpath)
{
	char		*temp;
	char		*update;

	temp = NULL;
	update = NULL;
	update = getcwd(update, 1024);
	if (update == NULL)
	{
		shell->status = ERR_CWD;
		ft_printf(STD_ERR, ERR_CWD_MSG);
		return (shell->status);
	}
	if (path != NULL)
	{
		temp = ft_strdup(path->value);
		shell->status = ms_cd_switch_path(path, update);
	}
	if (path != NULL && oldpath != NULL)
		shell->status = ms_cd_switch_path(oldpath, temp);
	if (update != NULL)
		free(update);
	if (temp != NULL)
		free(temp);
	return (shell->status);
}
