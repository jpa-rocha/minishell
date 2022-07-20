/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha <jrocha@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 12:26:27 by jrocha            #+#    #+#             */
/*   Updated: 2022/07/20 15:47:31 by jrocha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	ms_cd_switch_path(t_envvar *oldpath, char *newpath);
static int	ms_cd_path_exists(t_shell *shell, t_envvar *path,
				t_envvar *oldpath);
static int	ms_cd_new_path(t_shell *shell, t_envvar *path);
static int	ms_cd_new_oldpath(t_shell *shell, t_envvar *oldpath);

int	ms_cd(t_shell *shell, char *newpath)
{
	t_envvar	*oldpath;
	t_envvar	*path;

	oldpath = NULL;
	path = NULL;
	if (ms_env_find_entry(shell->workenv, "OLDPWD") != NULL)
		oldpath = (t_envvar *)
			ms_env_find_entry(shell->workenv, "OLDPWD")->data;
	if (ms_env_find_entry(shell->workenv, "PWD") != NULL)
		path = (t_envvar *) ms_env_find_entry(shell->workenv, "PWD")->data;
	shell->exitcode = EXIT_SUCCESS;
	if (newpath == NULL)
		ms_pwd();
	else if (chdir(newpath) == 0)
		shell->exitcode = ms_cd_path_exists(shell, path, oldpath);
	else
	{
		shell->exitcode = EXIT_FAILURE;
		printf("minishell: cd: %s: no such file or directory\n", newpath);
	}
	return (shell->exitcode);
}

static int	ms_cd_switch_path(t_envvar *oldpath, char *newpath)
{
	free(oldpath->value);
	oldpath->value = ft_calloc(ft_strlen(newpath) + 2, sizeof(char));
	if (oldpath->value == NULL)
		return (ALLOCATION_PROBLEM_EXIT);
	ft_strlcpy(oldpath->value, newpath, ft_strlen(newpath) + 1);
	return (EXIT_SUCCESS);
}

static int	ms_cd_path_exists(t_shell *shell, t_envvar *path,
				t_envvar *oldpath)
{
	char		*temp;
	char		*update;

	if (path == NULL || oldpath == NULL)
	{
		shell->exitcode = ms_cd_new_path(shell, path);
		path = (t_envvar *) ms_env_find_entry(shell->workenv, "PWD")->data;
	}
	if (oldpath == NULL)
	{
		shell->exitcode = ms_cd_new_oldpath(shell, oldpath);
		oldpath = (t_envvar *)
			ms_env_find_entry(shell->workenv, "OLDPWD")->data;
	}
	if (shell->exitcode == ALLOCATION_PROBLEM_EXIT)
		return (shell->exitcode);
	temp = ft_strdup(path->value);
	update = NULL;
	update = getcwd(update, 1024);
	shell->exitcode = ms_cd_switch_path(path, update);
	shell->exitcode = ms_cd_switch_path(oldpath, temp);
	if (update != NULL)
		free(update);
	free(temp);
	return (shell->exitcode);
}

static int	ms_cd_new_path(t_shell *shell, t_envvar *path)
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

static int	ms_cd_new_oldpath(t_shell *shell, t_envvar *oldpath)
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
